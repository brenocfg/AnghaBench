#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  size_t ssize_t ;
struct TYPE_9__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ pg_gssinfo ;
struct TYPE_10__ {int length; char* value; } ;
typedef  TYPE_2__ gss_buffer_desc ;
struct TYPE_11__ {TYPE_1__* gss; } ;
typedef  TYPE_3__ Port ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int PQ_GSS_RECV_BUFFER_SIZE ; 
 char* PqGSSRecvBuffer ; 
 int PqGSSRecvLength ; 
 char* PqGSSResultBuffer ; 
 int PqGSSResultLength ; 
 int PqGSSResultPointer ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_2__*) ; 
 scalar_t__ gss_unwrap (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_GSS_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 size_t secure_raw_read (TYPE_3__*,char*,int) ; 

ssize_t
be_gssapi_read(Port *port, void *ptr, size_t len)
{
	OM_uint32	major,
				minor;
	gss_buffer_desc input,
				output;
	ssize_t		ret;
	size_t		bytes_to_return = len;
	size_t		bytes_returned = 0;
	int			conf_state = 0;
	pg_gssinfo *gss = port->gss;

	/*
	 * The goal here is to read an incoming encrypted packet, one at a time,
	 * decrypt it into our out buffer, returning to the caller what they asked
	 * for, and then saving anything else for the next call.
	 *
	 * First we look to see if we have unencrypted bytes available and, if so,
	 * copy those to the result.  If the caller asked for more than we had
	 * immediately available, then we try to read a packet off the wire and
	 * decrypt it.  If the read would block, then return the amount of
	 * unencrypted data we copied into the caller's ptr.
	 */
	while (bytes_to_return)
	{
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
		 * wire then we return the number of unencrypted bytes we were able to
		 * copy (if any, if we didn't copy any, then we return whatever
		 * secure_raw_read returned when we called it; likely -1) into the
		 * caller's ptr and wait to be called again, until we get a full
		 * packet to decrypt.
		 */

		/* Check if we have the size of the packet already in our buffer. */
		if (PqGSSRecvLength < sizeof(uint32))
		{
			/*
			 * We were not able to get the length of the packet last time, so
			 * we need to do that first.
			 */
			ret = secure_raw_read(port, PqGSSRecvBuffer + PqGSSRecvLength,
								  sizeof(uint32) - PqGSSRecvLength);
			if (ret < 0)
				return bytes_returned ? bytes_returned : ret;

			PqGSSRecvLength += ret;

			/*
			 * If we only got part of the packet length, then return however
			 * many unencrypted bytes we copied to the caller and wait to be
			 * called again.
			 */
			if (PqGSSRecvLength < sizeof(uint32))
				return bytes_returned;
		}

		/*
		 * We have the length of the next packet at this point, so pull it out
		 * and then read whatever we have left of the packet to read.
		 */
		input.length = ntohl(*(uint32 *) PqGSSRecvBuffer);

		/* Check for over-length packet */
		if (input.length > PQ_GSS_RECV_BUFFER_SIZE - sizeof(uint32))
			ereport(FATAL,
					(errmsg("oversize GSSAPI packet sent by the client (%zu > %zu)",
							(size_t) input.length,
							PQ_GSS_RECV_BUFFER_SIZE - sizeof(uint32))));

		/*
		 * Read as much of the packet as we are able to on this call into
		 * wherever we left off from the last time we were called.
		 */
		ret = secure_raw_read(port, PqGSSRecvBuffer + PqGSSRecvLength,
							  input.length - (PqGSSRecvLength - sizeof(uint32)));
		if (ret < 0)
			return bytes_returned ? bytes_returned : ret;

		PqGSSRecvLength += ret;

		/*
		 * If we got less than the rest of the packet then we need to return
		 * and be called again.  If we didn't have any bytes to return on this
		 * run then return -1 and set errno to EWOULDBLOCK.
		 */
		if (PqGSSRecvLength - sizeof(uint32) < input.length)
		{
			if (!bytes_returned)
			{
				errno = EWOULDBLOCK;
				return -1;
			}

			return bytes_returned;
		}

		/*
		 * We now have the full packet and we can perform the decryption and
		 * refill our output buffer, then loop back up to pass that back to
		 * the user.
		 */
		output.value = NULL;
		output.length = 0;
		input.value = PqGSSRecvBuffer + sizeof(uint32);

		major = gss_unwrap(&minor, gss->ctx, &input, &output, &conf_state, NULL);
		if (major != GSS_S_COMPLETE)
			pg_GSS_error(FATAL, gettext_noop("GSSAPI unwrap error"),
						 major, minor);

		if (conf_state == 0)
			ereport(FATAL,
					(errmsg("incoming GSSAPI message did not use confidentiality")));

		memcpy(PqGSSResultBuffer, output.value, output.length);

		PqGSSResultLength = output.length;

		/* Our buffer is now empty, reset it */
		PqGSSRecvLength = 0;

		gss_release_buffer(&minor, &output);
	}

	return bytes_returned;
}