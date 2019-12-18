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
struct nn_ws_handshake {char const* response; char* expected_accept_key; int /*<<< orphan*/  accept_key_len; int /*<<< orphan*/ * accept_key; int /*<<< orphan*/  conn_len; int /*<<< orphan*/ * conn; int /*<<< orphan*/  upgrade_len; int /*<<< orphan*/ * upgrade; int /*<<< orphan*/  status_code_len; int /*<<< orphan*/ * status_code; int /*<<< orphan*/  extensions_len; int /*<<< orphan*/ * extensions; int /*<<< orphan*/  protocol_len; int /*<<< orphan*/ * protocol; int /*<<< orphan*/  version_len; int /*<<< orphan*/ * version; int /*<<< orphan*/  server_len; int /*<<< orphan*/ * server; int /*<<< orphan*/  reason_phrase_len; int /*<<< orphan*/ * reason_phrase; } ;

/* Variables and functions */
 char* CRLF ; 
 int NN_WS_HANDSHAKE_INVALID ; 
 int NN_WS_HANDSHAKE_MATCH ; 
 int NN_WS_HANDSHAKE_RECV_MORE ; 
 int /*<<< orphan*/  NN_WS_HANDSHAKE_TERMSEQ ; 
 int NN_WS_HANDSHAKE_VALID ; 
 int memchr (char const*,char,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_ws_match_token (char*,char const**,int,int /*<<< orphan*/ ) ; 
 int nn_ws_match_value (char*,char const**,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int nn_ws_validate_value (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strstr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nn_ws_handshake_parse_server_response (struct nn_ws_handshake *self)
{
    /*  As per RFC 6455 section 1.7, this parser is not intended to be a
        general-purpose parser for arbitrary HTTP headers. As with the design
        philosophy of nanomsg, application-specific exchanges are better
        reserved for accepted connections, not as fields within these
        headers. */

    int rc;
    const char *pos;

    /*  Guarantee that a NULL terminator exists to enable treating this
        recv buffer like a string. The lack of such would indicate a failure
        upstream to catch a buffer overflow. */
    nn_assert (memchr (self->response, '\0', sizeof (self->response)));

    /*  Having found the NULL terminator, from this point forward string
        functions may be used. */
    nn_assert (strlen (self->response) < sizeof (self->response));

    pos = self->response;

    /*  Is the response from the server fully received? */
    if (!strstr (pos, NN_WS_HANDSHAKE_TERMSEQ))
        return NN_WS_HANDSHAKE_RECV_MORE;

    self->status_code = NULL;
    self->reason_phrase = NULL;
    self->server = NULL;
    self->accept_key = NULL;
    self->upgrade = NULL;
    self->conn = NULL;
    self->version = NULL;
    self->protocol = NULL;

    self->status_code_len = 0;
    self->reason_phrase_len = 0;
    self->server_len = 0;
    self->accept_key_len = 0;
    self->upgrade_len = 0;
    self->conn_len = 0;
    self->version_len = 0;
    self->protocol_len = 0;

    /*  RFC 7230 3.1.2 Status Line: HTTP Version. */
    if (!nn_ws_match_token ("HTTP/1.1\x20", &pos, 0, 0))
        return NN_WS_HANDSHAKE_RECV_MORE;

    /*  RFC 7230 3.1.2 Status Line: Status Code. */
    if (!nn_ws_match_value ("\x20", &pos, 0, 0, &self->status_code,
        &self->status_code_len))
        return NN_WS_HANDSHAKE_RECV_MORE;

    /*  RFC 7230 3.1.2 Status Line: Reason Phrase. */
    if (!nn_ws_match_value (CRLF, &pos, 0, 0,
        &self->reason_phrase, &self->reason_phrase_len))
        return NN_WS_HANDSHAKE_RECV_MORE;

    /*  It's expected the current position is now at the first
        header field. Match them one by one. */
    while (strlen (pos))
    {
        if (nn_ws_match_token ("Server:", &pos, 1, 0)) {
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                &self->server, &self->server_len);
        }
        else if (nn_ws_match_token ("Sec-WebSocket-Accept:",
            &pos, 1, 0) == NN_WS_HANDSHAKE_MATCH) {
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                &self->accept_key, &self->accept_key_len);
        }
        else if (nn_ws_match_token ("Upgrade:",
            &pos, 1, 0) == NN_WS_HANDSHAKE_MATCH) {
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                &self->upgrade, &self->upgrade_len);
        }
        else if (nn_ws_match_token ("Connection:",
            &pos, 1, 0) == NN_WS_HANDSHAKE_MATCH) {
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                &self->conn, &self->conn_len);
        }
        else if (nn_ws_match_token ("Sec-WebSocket-Version-Server:",
            &pos, 1, 0) == NN_WS_HANDSHAKE_MATCH) {
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                &self->version, &self->version_len);
        }
        else if (nn_ws_match_token ("Sec-WebSocket-Protocol-Server:",
            &pos, 1, 0) == NN_WS_HANDSHAKE_MATCH) {
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                &self->protocol, &self->protocol_len);
        }
        else if (nn_ws_match_token ("Sec-WebSocket-Extensions:",
            &pos, 1, 0) == NN_WS_HANDSHAKE_MATCH) {
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                &self->extensions, &self->extensions_len);
        }
        else if (nn_ws_match_token (CRLF,
            &pos, 1, 0) == NN_WS_HANDSHAKE_MATCH) {
            /*  Exit loop since all headers are parsed. */
            break;
        }
        else {
            /*  Skip unknown headers. */
            rc = nn_ws_match_value (CRLF, &pos, 1, 1,
                NULL, NULL);
        }

        if (rc != NN_WS_HANDSHAKE_MATCH)
            return NN_WS_HANDSHAKE_RECV_MORE;
    }

    /*  Validate the opening handshake is now fully parsed. Additionally,
        as per RFC 6455 section 4.1, the client should not send additional data
        after the opening handshake, so this assertion validates upstream recv
        logic prevented this case. */
    nn_assert (strlen (pos) == 0);

    /*  TODO: protocol expectations below this point are hard-coded here as
        an initial design decision. Perhaps in the future these values should
        be settable via compile time (or run-time socket) options? */

    /*  These header fields are required as per RFC 6455 4.2.2. */
    if (!self->status_code || !self->upgrade || !self->conn ||
        !self->accept_key)
        return NN_WS_HANDSHAKE_INVALID;

    /*  TODO: Currently, we only handle a successful connection upgrade.
        Anything else is treated as a failed connection.
        Consider handling other scenarios like 3xx redirects. */
    if (nn_ws_validate_value ("101", self->status_code,
        self->status_code_len, 1) != NN_WS_HANDSHAKE_MATCH)
        return NN_WS_HANDSHAKE_INVALID;

    /*  RFC 6455 section 4.2.2.5.2 (version December 2011). */
    if (nn_ws_validate_value ("websocket", self->upgrade,
        self->upgrade_len, 1) != NN_WS_HANDSHAKE_MATCH)
        return NN_WS_HANDSHAKE_INVALID;

    /*  RFC 6455 section 4.2.2.5.3 (version December 2011). */
    if (nn_ws_validate_value ("Upgrade", self->conn,
        self->conn_len, 1) != NN_WS_HANDSHAKE_MATCH)
        return NN_WS_HANDSHAKE_INVALID;

    /*  RFC 6455 section 4.2.2.5.4 (version December 2011). */
    if (nn_ws_validate_value (self->expected_accept_key, self->accept_key,
        self->accept_key_len, 1) != NN_WS_HANDSHAKE_MATCH)
        return NN_WS_HANDSHAKE_INVALID;

    /*  Server response meets RFC 6455 compliance for opening handshake. */
    return NN_WS_HANDSHAKE_VALID;
}