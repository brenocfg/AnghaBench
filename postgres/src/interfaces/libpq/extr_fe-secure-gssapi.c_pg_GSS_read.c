#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  size_t ssize_t ;
struct TYPE_10__ {int length; char* value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
struct TYPE_11__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  gctx; } ;
typedef  TYPE_2__ PGconn ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 TYPE_1__ GSS_C_EMPTY_BUFFER ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int PQ_GSS_RECV_BUFFER_SIZE ; 
 char* PqGSSRecvBuffer ; 
 int PqGSSRecvLength ; 
 int PqGSSRecvPointer ; 
 char* PqGSSResultBuffer ; 
 int PqGSSResultLength ; 
 int PqGSSResultPointer ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_unwrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_GSS_error (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t pqsecure_raw_read (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

ssize_t
pg_GSS_read(PGconn *conn, void *ptr, size_t len)
{
	OM_uint32	major,
				minor;
	gss_buffer_desc input = GSS_C_EMPTY_BUFFER,
				output = GSS_C_EMPTY_BUFFER;
	ssize_t		ret = 0;
	size_t		bytes_to_return = len;
	size_t		bytes_returned = 0;

	/*
	 * The goal here is to read an incoming encrypted packet, one at a time,
	 * decrypt it into our out buffer, returning to the caller what they asked
	 * for, and then saving anything else for the next call.
	 *
	 * We get a read request, we look if we have cleartext bytes available
	 * and, if so, copy those to the result, and then we try to decrypt the
	 * next packet.
	 *
	 * We should not try to decrypt the next packet until the read buffer is
	 * completely empty.
	 *
	 * If the caller asks for more bytes than one decrypted packet, then we
	 * should try to return all bytes asked for.
	 */
	while (bytes_to_return)
	{
		int			conf_state = 0;

		/* Check if we have data in our buffer that we can return immediately */
		if (PqGSSResultPointer < PqGSSResultLength)
		{
			int			bytes_in_buffer = PqGSSResultLength - PqGSSResultPointer;
			int			bytes_to_copy = bytes_in_buffer < len - bytes_returned ? bytes_in_buffer : len - bytes_returned;

			/*
			 * Copy the data from our output buffer into the caller's buffer,
			 * at the point where we last left off filling their buffer
			 */
			memcpy((char *) ptr + bytes_returned, PqGSSResultBuffer + PqGSSResultPointer, bytes_to_copy);
			PqGSSResultPointer += bytes_to_copy;
			bytes_to_return -= bytes_to_copy;
			bytes_returned += bytes_to_copy;

			/* Check if our result buffer is now empty and, if so, reset */
			if (PqGSSResultPointer == PqGSSResultLength)
				PqGSSResultPointer = PqGSSResultLength = 0;

			continue;
		}

		/*
		 * At this point, our output buffer should be empty with more bytes
		 * being requested to be read.  We are now ready to load the next
		 * packet and decrypt it (entirely) into our buffer.
		 *
		 * If we get a partial read back while trying to read a packet off the
		 * wire then we return back what bytes we were able to return and wait
		 * to be called again, until we get a full packet to decrypt.
		 */

		/* Check if we got a partial read just trying to get the length */
		if (PqGSSRecvLength < sizeof(uint32))
		{
			/* Try to get whatever of the length we still need */
			ret = pqsecure_raw_read(conn, PqGSSRecvBuffer + PqGSSRecvLength,
									sizeof(uint32) - PqGSSRecvLength);
			if (ret < 0)
				return bytes_returned ? bytes_returned : ret;

			PqGSSRecvLength += ret;
			if (PqGSSRecvLength < sizeof(uint32))
				return bytes_returned;
		}

		/*
		 * We should have the whole length at this point, so pull it out and
		 * then read whatever we have left of the packet
		 */
		input.length = ntohl(*(uint32 *) PqGSSRecvBuffer);

		/* Check for over-length packet */
		if (input.length > PQ_GSS_RECV_BUFFER_SIZE - sizeof(uint32))
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("oversize GSSAPI packet sent by the server (%zu > %zu)\n"),
							  (size_t) input.length,
							  PQ_GSS_RECV_BUFFER_SIZE - sizeof(uint32));
			ret = -1;
			goto cleanup;
		}

		/*
		 * Read as much of the packet as we are able to on this call into
		 * wherever we left off from the last time we were called.
		 */
		ret = pqsecure_raw_read(conn, PqGSSRecvBuffer + PqGSSRecvLength,
								input.length - (PqGSSRecvLength - sizeof(uint32)));
		if (ret < 0)
			return bytes_returned ? bytes_returned : ret;

		/*
		 * If we got less than the rest of the packet then we need to return
		 * and be called again.
		 */
		PqGSSRecvLength += ret;
		if (PqGSSRecvLength - sizeof(uint32) < input.length)
			return bytes_returned ? bytes_returned : -1;

		/*
		 * We now have the full packet and we can perform the decryption and
		 * refill our output buffer, then loop back up to pass that back to
		 * the user.
		 */
		output.value = NULL;
		output.length = 0;
		input.value = PqGSSRecvBuffer + sizeof(uint32);

		major = gss_unwrap(&minor, conn->gctx, &input, &output, &conf_state, NULL);
		if (major != GSS_S_COMPLETE)
		{
			pg_GSS_error(libpq_gettext("GSSAPI unwrap error"), conn,
						 major, minor);
			ret = -1;
			goto cleanup;
		}
		else if (conf_state == 0)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("incoming GSSAPI message did not use confidentiality\n"));
			ret = -1;
			goto cleanup;
		}

		memcpy(PqGSSResultBuffer, output.value, output.length);
		PqGSSResultLength = output.length;

		/* Our buffer is now empty, reset it */
		PqGSSRecvPointer = PqGSSRecvLength = 0;

		gss_release_buffer(&minor, &output);
	}

	ret = bytes_returned;

cleanup:
	if (output.value != NULL)
		gss_release_buffer(&minor, &output);
	return ret;
}