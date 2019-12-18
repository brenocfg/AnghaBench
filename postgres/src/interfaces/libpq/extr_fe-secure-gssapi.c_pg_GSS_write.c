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
typedef  char uint32 ;
typedef  scalar_t__ ssize_t ;
struct TYPE_10__ {size_t length; char* value; } ;
typedef  TYPE_1__ gss_buffer_desc ;
struct TYPE_11__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  gctx; } ;
typedef  TYPE_2__ PGconn ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 TYPE_1__ GSS_C_EMPTY_BUFFER ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int PQ_GSS_SEND_BUFFER_SIZE ; 
 scalar_t__ PqGSSSendBuffer ; 
 scalar_t__ PqGSSSendPointer ; 
 scalar_t__ PqGSSSendStart ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gss_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int*,TYPE_1__*) ; 
 char htonl (size_t) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 size_t max_packet_size ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  pg_GSS_error (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pqsecure_raw_write (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

ssize_t
pg_GSS_write(PGconn *conn, const void *ptr, size_t len)
{
	gss_buffer_desc input,
				output = GSS_C_EMPTY_BUFFER;
	OM_uint32	major,
				minor;
	ssize_t		ret = -1;
	size_t		bytes_to_encrypt = len;
	size_t		bytes_encrypted = 0;

	/*
	 * Loop through encrypting data and sending it out until
	 * pqsecure_raw_write() complains (which would likely mean that the socket
	 * is non-blocking and the requested send() would block, or there was some
	 * kind of actual error) and then return.
	 */
	while (bytes_to_encrypt || PqGSSSendPointer)
	{
		int			conf_state = 0;
		uint32		netlen;

		/*
		 * Check if we have data in the encrypted output buffer that needs to
		 * be sent, and if so, try to send it.  If we aren't able to, return
		 * that back up to the caller.
		 */
		if (PqGSSSendPointer)
		{
			ssize_t		ret;
			ssize_t		amount = PqGSSSendPointer - PqGSSSendStart;

			ret = pqsecure_raw_write(conn, PqGSSSendBuffer + PqGSSSendStart, amount);
			if (ret < 0)
			{
				/*
				 * If we encrypted some data and it's in our output buffer,
				 * but send() is saying that we would block, then tell the
				 * client how far we got with encrypting the data so that they
				 * can call us again with whatever is left, at which point we
				 * will try to send the remaining encrypted data first and
				 * then move on to encrypting the rest of the data.
				 */
				if (bytes_encrypted != 0 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
					return bytes_encrypted;
				else
					return ret;
			}

			/*
			 * Partial write, move forward that far in our buffer and try
			 * again
			 */
			if (ret != amount)
			{
				PqGSSSendStart += ret;
				continue;
			}

			/* All encrypted data was sent, our buffer is empty now. */
			PqGSSSendPointer = PqGSSSendStart = 0;
		}

		/*
		 * Check if there are any bytes left to encrypt.  If not, we're done.
		 */
		if (!bytes_to_encrypt)
			return bytes_encrypted;

		/*
		 * Check how much we are being asked to send, if it's too much, then
		 * we will have to loop and possibly be called multiple times to get
		 * through all the data.
		 */
		if (bytes_to_encrypt > max_packet_size)
			input.length = max_packet_size;
		else
			input.length = bytes_to_encrypt;

		input.value = (char *) ptr + bytes_encrypted;

		output.value = NULL;
		output.length = 0;

		/* Create the next encrypted packet */
		major = gss_wrap(&minor, conn->gctx, 1, GSS_C_QOP_DEFAULT,
						 &input, &conf_state, &output);
		if (major != GSS_S_COMPLETE)
		{
			pg_GSS_error(libpq_gettext("GSSAPI wrap error"), conn, major, minor);
			goto cleanup;
		}
		else if (conf_state == 0)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("outgoing GSSAPI message would not use confidentiality\n"));
			goto cleanup;
		}

		if (output.length > PQ_GSS_SEND_BUFFER_SIZE - sizeof(uint32))
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("client tried to send oversize GSSAPI packet (%zu > %zu)\n"),
							  (size_t) output.length,
							  PQ_GSS_SEND_BUFFER_SIZE - sizeof(uint32));
			goto cleanup;
		}

		bytes_encrypted += input.length;
		bytes_to_encrypt -= input.length;

		/* 4 network-order bytes of length, then payload */
		netlen = htonl(output.length);
		memcpy(PqGSSSendBuffer + PqGSSSendPointer, &netlen, sizeof(uint32));
		PqGSSSendPointer += sizeof(uint32);

		memcpy(PqGSSSendBuffer + PqGSSSendPointer, output.value, output.length);
		PqGSSSendPointer += output.length;
	}

	ret = bytes_encrypted;

cleanup:
	if (output.value != NULL)
		gss_release_buffer(&minor, &output);
	return ret;
}