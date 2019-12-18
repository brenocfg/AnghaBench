#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32 ;
typedef  scalar_t__ ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ pg_gssinfo ;
struct TYPE_9__ {size_t length; char* value; } ;
typedef  TYPE_2__ gss_buffer_desc ;
struct TYPE_10__ {TYPE_1__* gss; } ;
typedef  TYPE_3__ Port ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GSS_C_QOP_DEFAULT ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int PQ_GSS_SEND_BUFFER_SIZE ; 
 scalar_t__ PqGSSSendBuffer ; 
 scalar_t__ PqGSSSendPointer ; 
 scalar_t__ PqGSSSendStart ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 scalar_t__ gss_wrap (scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*,int*,TYPE_2__*) ; 
 char htonl (size_t) ; 
 size_t max_packet_size ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  pg_GSS_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ secure_raw_write (TYPE_3__*,scalar_t__,scalar_t__) ; 

ssize_t
be_gssapi_write(Port *port, void *ptr, size_t len)
{
	size_t		bytes_to_encrypt = len;
	size_t		bytes_encrypted = 0;

	/*
	 * Loop through encrypting data and sending it out until
	 * secure_raw_write() complains (which would likely mean that the socket
	 * is non-blocking and the requested send() would block, or there was some
	 * kind of actual error) and then return.
	 */
	while (bytes_to_encrypt || PqGSSSendPointer)
	{
		OM_uint32	major,
					minor;
		gss_buffer_desc input,
					output;
		int			conf_state = 0;
		uint32		netlen;
		pg_gssinfo *gss = port->gss;

		/*
		 * Check if we have data in the encrypted output buffer that needs to
		 * be sent, and if so, try to send it.  If we aren't able to, return
		 * that back up to the caller.
		 */
		if (PqGSSSendPointer)
		{
			ssize_t		ret;
			ssize_t		amount = PqGSSSendPointer - PqGSSSendStart;

			ret = secure_raw_write(port, PqGSSSendBuffer + PqGSSSendStart, amount);
			if (ret <= 0)
			{
				/*
				 * If we encrypted some data and it's in our output buffer,
				 * but send() is saying that we would block, then tell the
				 * caller how far we got with encrypting the data so that they
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
			 * Check if this was a partial write, and if so, move forward that
			 * far in our buffer and try again.
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
		 * max_packet_size is the maximum amount of unencrypted data that,
		 * when encrypted, will fit into our encrypted-data output buffer.
		 *
		 * If we are being asked to send more than max_packet_size unencrypted
		 * data, then we will loop and create multiple packets, each with
		 * max_packet_size unencrypted data encrypted in them (at least, until
		 * secure_raw_write returns a failure saying we would be blocked, at
		 * which point we will let the caller know how far we got).
		 */
		if (bytes_to_encrypt > max_packet_size)
			input.length = max_packet_size;
		else
			input.length = bytes_to_encrypt;

		input.value = (char *) ptr + bytes_encrypted;

		output.value = NULL;
		output.length = 0;

		/* Create the next encrypted packet */
		major = gss_wrap(&minor, gss->ctx, 1, GSS_C_QOP_DEFAULT,
						 &input, &conf_state, &output);
		if (major != GSS_S_COMPLETE)
			pg_GSS_error(FATAL, gettext_noop("GSSAPI wrap error"), major, minor);

		if (conf_state == 0)
			ereport(FATAL,
					(errmsg("outgoing GSSAPI message would not use confidentiality")));

		if (output.length > PQ_GSS_SEND_BUFFER_SIZE - sizeof(uint32))
			ereport(FATAL,
					(errmsg("server tried to send oversize GSSAPI packet (%zu > %zu)",
							(size_t) output.length,
							PQ_GSS_SEND_BUFFER_SIZE - sizeof(uint32))));

		bytes_encrypted += input.length;
		bytes_to_encrypt -= input.length;

		/* 4 network-order length bytes, then payload */
		netlen = htonl(output.length);
		memcpy(PqGSSSendBuffer + PqGSSSendPointer, &netlen, sizeof(uint32));
		PqGSSSendPointer += sizeof(uint32);

		memcpy(PqGSSSendBuffer + PqGSSSendPointer, output.value, output.length);
		PqGSSSendPointer += output.length;
	}

	return bytes_encrypted;
}