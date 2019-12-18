#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char cbind_flag; void* client_nonce; void* client_username; void* client_first_message_bare; int /*<<< orphan*/  channel_binding_in_use; TYPE_1__* port; } ;
typedef  TYPE_2__ scram_state ;
struct TYPE_4__ {int /*<<< orphan*/  ssl_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  is_scram_printable (void*) ; 
 void* pstrdup (char const*) ; 
 int /*<<< orphan*/  read_any_attr (char**,int /*<<< orphan*/ *) ; 
 void* read_attr_value (char**,char) ; 
 int /*<<< orphan*/  sanitize_char (char) ; 
 int /*<<< orphan*/  sanitize_str (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
read_client_first_message(scram_state *state, const char *input)
{
	char	   *p = pstrdup(input);
	char	   *channel_binding_type;


	/*------
	 * The syntax for the client-first-message is: (RFC 5802)
	 *
	 * saslname		   = 1*(value-safe-char / "=2C" / "=3D")
	 *					 ;; Conforms to <value>.
	 *
	 * authzid		   = "a=" saslname
	 *					 ;; Protocol specific.
	 *
	 * cb-name		   = 1*(ALPHA / DIGIT / "." / "-")
	 *					  ;; See RFC 5056, Section 7.
	 *					  ;; E.g., "tls-server-end-point" or
	 *					  ;; "tls-unique".
	 *
	 * gs2-cbind-flag  = ("p=" cb-name) / "n" / "y"
	 *					 ;; "n" -> client doesn't support channel binding.
	 *					 ;; "y" -> client does support channel binding
	 *					 ;;		   but thinks the server does not.
	 *					 ;; "p" -> client requires channel binding.
	 *					 ;; The selected channel binding follows "p=".
	 *
	 * gs2-header	   = gs2-cbind-flag "," [ authzid ] ","
	 *					 ;; GS2 header for SCRAM
	 *					 ;; (the actual GS2 header includes an optional
	 *					 ;; flag to indicate that the GSS mechanism is not
	 *					 ;; "standard", but since SCRAM is "standard", we
	 *					 ;; don't include that flag).
	 *
	 * username		   = "n=" saslname
	 *					 ;; Usernames are prepared using SASLprep.
	 *
	 * reserved-mext  = "m=" 1*(value-char)
	 *					 ;; Reserved for signaling mandatory extensions.
	 *					 ;; The exact syntax will be defined in
	 *					 ;; the future.
	 *
	 * nonce		   = "r=" c-nonce [s-nonce]
	 *					 ;; Second part provided by server.
	 *
	 * c-nonce		   = printable
	 *
	 * client-first-message-bare =
	 *					 [reserved-mext ","]
	 *					 username "," nonce ["," extensions]
	 *
	 * client-first-message =
	 *					 gs2-header client-first-message-bare
	 *
	 * For example:
	 * n,,n=user,r=fyko+d2lbbFgONRv9qkxdawL
	 *
	 * The "n,," in the beginning means that the client doesn't support
	 * channel binding, and no authzid is given.  "n=user" is the username.
	 * However, in PostgreSQL the username is sent in the startup packet, and
	 * the username in the SCRAM exchange is ignored.  libpq always sends it
	 * as an empty string.  The last part, "r=fyko+d2lbbFgONRv9qkxdawL" is
	 * the client nonce.
	 *------
	 */

	/*
	 * Read gs2-cbind-flag.  (For details see also RFC 5802 Section 6 "Channel
	 * Binding".)
	 */
	state->cbind_flag = *p;
	switch (*p)
	{
		case 'n':

			/*
			 * The client does not support channel binding or has simply
			 * decided to not use it.  In that case just let it go.
			 */
			if (state->channel_binding_in_use)
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("malformed SCRAM message"),
						 errdetail("The client selected SCRAM-SHA-256-PLUS, but the SCRAM message does not include channel binding data.")));

			p++;
			if (*p != ',')
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("malformed SCRAM message"),
						 errdetail("Comma expected, but found character \"%s\".",
								   sanitize_char(*p))));
			p++;
			break;
		case 'y':

			/*
			 * The client supports channel binding and thinks that the server
			 * does not.  In this case, the server must fail authentication if
			 * it supports channel binding.
			 */
			if (state->channel_binding_in_use)
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("malformed SCRAM message"),
						 errdetail("The client selected SCRAM-SHA-256-PLUS, but the SCRAM message does not include channel binding data.")));

#ifdef HAVE_BE_TLS_GET_CERTIFICATE_HASH
			if (state->port->ssl_in_use)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION),
						 errmsg("SCRAM channel binding negotiation error"),
						 errdetail("The client supports SCRAM channel binding but thinks the server does not.  "
								   "However, this server does support channel binding.")));
#endif
			p++;
			if (*p != ',')
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("malformed SCRAM message"),
						 errdetail("Comma expected, but found character \"%s\".",
								   sanitize_char(*p))));
			p++;
			break;
		case 'p':

			/*
			 * The client requires channel binding.  Channel binding type
			 * follows, e.g., "p=tls-server-end-point".
			 */
			if (!state->channel_binding_in_use)
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("malformed SCRAM message"),
						 errdetail("The client selected SCRAM-SHA-256 without channel binding, but the SCRAM message includes channel binding data.")));

			channel_binding_type = read_attr_value(&p, 'p');

			/*
			 * The only channel binding type we support is
			 * tls-server-end-point.
			 */
			if (strcmp(channel_binding_type, "tls-server-end-point") != 0)
				ereport(ERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 (errmsg("unsupported SCRAM channel-binding type \"%s\"",
								 sanitize_str(channel_binding_type)))));
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("malformed SCRAM message"),
					 errdetail("Unexpected channel-binding flag \"%s\".",
							   sanitize_char(*p))));
	}

	/*
	 * Forbid optional authzid (authorization identity).  We don't support it.
	 */
	if (*p == 'a')
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("client uses authorization identity, but it is not supported")));
	if (*p != ',')
		ereport(ERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("malformed SCRAM message"),
				 errdetail("Unexpected attribute \"%s\" in client-first-message.",
						   sanitize_char(*p))));
	p++;

	state->client_first_message_bare = pstrdup(p);

	/*
	 * Any mandatory extensions would go here.  We don't support any.
	 *
	 * RFC 5802 specifies error code "e=extensions-not-supported" for this,
	 * but it can only be sent in the server-final message.  We prefer to fail
	 * immediately (which the RFC also allows).
	 */
	if (*p == 'm')
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("client requires an unsupported SCRAM extension")));

	/*
	 * Read username.  Note: this is ignored.  We use the username from the
	 * startup message instead, still it is kept around if provided as it
	 * proves to be useful for debugging purposes.
	 */
	state->client_username = read_attr_value(&p, 'n');

	/* read nonce and check that it is made of only printable characters */
	state->client_nonce = read_attr_value(&p, 'r');
	if (!is_scram_printable(state->client_nonce))
		ereport(ERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("non-printable characters in SCRAM nonce")));

	/*
	 * There can be any number of optional extensions after this.  We don't
	 * support any extensions, so ignore them.
	 */
	while (*p != '\0')
		read_any_attr(&p, NULL);

	/* success! */
}