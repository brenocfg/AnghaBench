#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  int uint32 ;
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  void* RD_BOOL ;

/* Variables and functions */
 void* False ; 
#define  HYBRID_REQUIRED_BY_SERVER 133 
#define  INCONSISTENT_FLAGS 132 
 scalar_t__ ISO_PDU_CC ; 
 int PROTOCOL_HYBRID ; 
 int PROTOCOL_RDP ; 
 int PROTOCOL_SSL ; 
 scalar_t__ RDP_NEG_FAILURE ; 
 scalar_t__ RDP_NEG_RSP ; 
 scalar_t__ RDP_V5 ; 
#define  SSL_CERT_NOT_ON_SERVER 131 
#define  SSL_NOT_ALLOWED_BY_SERVER 130 
#define  SSL_REQUIRED_BY_SERVER 129 
#define  SSL_WITH_USER_AUTH_REQUIRED_BY_SERVER 128 
 void* True ; 
 int /*<<< orphan*/  cssp_connect (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 void* g_encryption ; 
 void* g_negotiate_rdp_protocol ; 
 scalar_t__ g_rdp_version ; 
 scalar_t__ g_sc_card_name ; 
 scalar_t__ g_sc_container_name ; 
 scalar_t__ g_sc_csp_name ; 
 scalar_t__ g_sc_reader_name ; 
 int /*<<< orphan*/  g_use_password_as_pin ; 
 int /*<<< orphan*/  in_uint16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  in_uint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * iso_recv_msg (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iso_send_connection_request (char*,int) ; 
 scalar_t__ s_check_rem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcp_connect (char*) ; 
 int /*<<< orphan*/  tcp_disconnect () ; 
 int /*<<< orphan*/  tcp_tls_connect () ; 
 int /*<<< orphan*/  warning (char*) ; 

RD_BOOL
iso_connect(char *server, char *username, char *domain, char *password,
	    RD_BOOL reconnect, uint32 * selected_protocol)
{
	STREAM s;
	uint8 code;
	uint32 neg_proto;

	g_negotiate_rdp_protocol = True;

	neg_proto = PROTOCOL_SSL;

#ifdef WITH_CREDSSP
	if (!g_use_password_as_pin)
		neg_proto |= PROTOCOL_HYBRID;
	else if (g_sc_csp_name || g_sc_reader_name || g_sc_card_name || g_sc_container_name)
		neg_proto |= PROTOCOL_HYBRID;
	else
		warning("Disables CredSSP due to missing smartcard information for SSO.\n");
#endif

      retry:
	*selected_protocol = PROTOCOL_RDP;
	code = 0;

	if (!tcp_connect(server))
		return False;

	iso_send_connection_request(username, neg_proto);

	s = iso_recv_msg(&code, NULL);
	if (s == NULL)
		return False;

	if (code != ISO_PDU_CC)
	{
		error("expected CC, got 0x%x\n", code);
		tcp_disconnect();
		return False;
	}

	if (g_rdp_version >= RDP_V5 && s_check_rem(s, 8))
	{
		/* handle RDP_NEG_REQ response */
		const char *reason = NULL;

		uint8 type = 0, flags = 0;
		uint16 length = 0;
		uint32 data = 0;

		in_uint8(s, type);
		in_uint8(s, flags);
		in_uint16(s, length);
		in_uint32(s, data);

		if (type == RDP_NEG_FAILURE)
		{
			RD_BOOL retry_without_neg = False;

			switch (data)
			{
				case SSL_WITH_USER_AUTH_REQUIRED_BY_SERVER:
					reason = "SSL with user authentication required by server";
					break;
				case SSL_NOT_ALLOWED_BY_SERVER:
					reason = "SSL not allowed by server";
					retry_without_neg = True;
					break;
				case SSL_CERT_NOT_ON_SERVER:
					reason = "no valid authentication certificate on server";
					retry_without_neg = True;
					break;
				case INCONSISTENT_FLAGS:
					reason = "inconsistent negotiation flags";
					break;
				case SSL_REQUIRED_BY_SERVER:
					reason = "SSL required by server";
					break;
				case HYBRID_REQUIRED_BY_SERVER:
					reason = "CredSSP required by server";
					break;
				default:
					reason = "unknown reason";
			}

			tcp_disconnect();

			if (retry_without_neg)
			{
				fprintf(stderr,
					"Failed to negotiate protocol, retrying with plain RDP.\n");
				g_negotiate_rdp_protocol = False;
				goto retry;
			}

			fprintf(stderr, "Failed to connect, %s.\n", reason);
			return False;
		}

		if (type != RDP_NEG_RSP)
		{
			tcp_disconnect();
			error("Expected RDP_NEG_RSP, got type = 0x%x\n", type);
			return False;
		}

		/* handle negotiation response */
		if (data == PROTOCOL_SSL)
		{
#ifdef WITH_SSL
			if (!tcp_tls_connect())
			{
				/* failed to connect using cssp, let retry with plain TLS */
				tcp_disconnect();
				neg_proto = PROTOCOL_RDP;
				goto retry;
			}
			/* do not use encryption when using TLS */
			g_encryption = False;
			fprintf(stderr, "Connection established using SSL.\n");
#else /* WITH_SSL */
			fprintf(stderr, "SSL not compiled in.\n");
#endif /* WITH_SSL */
		}
#ifdef WITH_CREDSSP
		else if (data == PROTOCOL_HYBRID)
		{
			if (!cssp_connect(server, username, domain, password, s))
			{
				/* failed to connect using cssp, let retry with plain TLS */
				tcp_disconnect();
				neg_proto = PROTOCOL_SSL;
				goto retry;
			}

			/* do not use encryption when using TLS */
			fprintf(stderr, "Connection established using CredSSP.\n");
			g_encryption = False;
		}
#endif
		else if (data == PROTOCOL_RDP)
		{
			fprintf(stderr, "Connection established using plain RDP.\n");
		}
		else if (data != PROTOCOL_RDP)
		{
			tcp_disconnect();
			error("Unexpected protocol in negotiation response, got data = 0x%x.\n",
			      data);
			return False;
		}
		if (length || flags) {}

		*selected_protocol = data;
	}
	return True;
}