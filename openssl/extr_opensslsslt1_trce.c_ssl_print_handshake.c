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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_dump_indent (int /*<<< orphan*/ *,char const*,size_t,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,unsigned char const,unsigned char const,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
#define  DTLS1_MT_HELLO_VERIFY_REQUEST 140 
#define  SSL3_MT_CERTIFICATE 139 
#define  SSL3_MT_CERTIFICATE_REQUEST 138 
#define  SSL3_MT_CERTIFICATE_VERIFY 137 
#define  SSL3_MT_CLIENT_HELLO 136 
#define  SSL3_MT_CLIENT_KEY_EXCHANGE 135 
#define  SSL3_MT_ENCRYPTED_EXTENSIONS 134 
#define  SSL3_MT_FINISHED 133 
#define  SSL3_MT_KEY_UPDATE 132 
#define  SSL3_MT_NEWSESSION_TICKET 131 
#define  SSL3_MT_SERVER_DONE 130 
#define  SSL3_MT_SERVER_HELLO 129 
#define  SSL3_MT_SERVER_KEY_EXCHANGE 128 
 scalar_t__ SSL_IS_DTLS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dtls_print_hello_vfyrequest (int /*<<< orphan*/ *,int,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_handshake_tbl ; 
 int /*<<< orphan*/  ssl_key_update_tbl ; 
 int /*<<< orphan*/  ssl_print_cert_request (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_certificates (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_client_hello (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_client_keyex (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_extensions (int /*<<< orphan*/ *,int,int,int const,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_hex (int /*<<< orphan*/ *,int,char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_server_hello (int /*<<< orphan*/ *,int,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_server_keyex (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_print_signature (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_ticket (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_trace_list (int /*<<< orphan*/ *,int,unsigned char const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_trace_str (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_print_handshake(BIO *bio, const SSL *ssl, int server,
                               const unsigned char *msg, size_t msglen,
                               int indent)
{
    size_t hlen;
    unsigned char htype;

    if (msglen < 4)
        return 0;
    htype = msg[0];
    hlen = (msg[1] << 16) | (msg[2] << 8) | msg[3];
    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "%s, Length=%d\n",
               ssl_trace_str(htype, ssl_handshake_tbl), (int)hlen);
    msg += 4;
    msglen -= 4;
    if (SSL_IS_DTLS(ssl)) {
        if (msglen < 8)
            return 0;
        BIO_indent(bio, indent, 80);
        BIO_printf(bio, "message_seq=%d, fragment_offset=%d, "
                   "fragment_length=%d\n",
                   (msg[0] << 8) | msg[1],
                   (msg[2] << 16) | (msg[3] << 8) | msg[4],
                   (msg[5] << 16) | (msg[6] << 8) | msg[7]);
        msg += 8;
        msglen -= 8;
    }
    if (msglen < hlen)
        return 0;
    switch (htype) {
    case SSL3_MT_CLIENT_HELLO:
        if (!ssl_print_client_hello(bio, ssl, indent + 2, msg, msglen))
            return 0;
        break;

    case DTLS1_MT_HELLO_VERIFY_REQUEST:
        if (!dtls_print_hello_vfyrequest(bio, indent + 2, msg, msglen))
            return 0;
        break;

    case SSL3_MT_SERVER_HELLO:
        if (!ssl_print_server_hello(bio, indent + 2, msg, msglen))
            return 0;
        break;

    case SSL3_MT_SERVER_KEY_EXCHANGE:
        if (!ssl_print_server_keyex(bio, indent + 2, ssl, msg, msglen))
            return 0;
        break;

    case SSL3_MT_CLIENT_KEY_EXCHANGE:
        if (!ssl_print_client_keyex(bio, indent + 2, ssl, msg, msglen))
            return 0;
        break;

    case SSL3_MT_CERTIFICATE:
        if (!ssl_print_certificates(bio, ssl, server, indent + 2, msg, msglen))
            return 0;
        break;

    case SSL3_MT_CERTIFICATE_VERIFY:
        if (!ssl_print_signature(bio, indent + 2, ssl, &msg, &msglen))
            return 0;
        break;

    case SSL3_MT_CERTIFICATE_REQUEST:
        if (!ssl_print_cert_request(bio, indent + 2, ssl, msg, msglen))
            return 0;
        break;

    case SSL3_MT_FINISHED:
        ssl_print_hex(bio, indent + 2, "verify_data", msg, msglen);
        break;

    case SSL3_MT_SERVER_DONE:
        if (msglen != 0)
            ssl_print_hex(bio, indent + 2, "unexpected value", msg, msglen);
        break;

    case SSL3_MT_NEWSESSION_TICKET:
        if (!ssl_print_ticket(bio, indent + 2, ssl, msg, msglen))
            return 0;
        break;

    case SSL3_MT_ENCRYPTED_EXTENSIONS:
        if (!ssl_print_extensions(bio, indent + 2, 1,
                                  SSL3_MT_ENCRYPTED_EXTENSIONS, &msg, &msglen))
            return 0;
        break;

    case SSL3_MT_KEY_UPDATE:
        if (msglen != 1) {
            ssl_print_hex(bio, indent + 2, "unexpected value", msg, msglen);
            return 0;
        }
        if (!ssl_trace_list(bio, indent + 2, msg, msglen, 1,
                            ssl_key_update_tbl))
            return 0;
        break;

    default:
        BIO_indent(bio, indent + 2, 80);
        BIO_puts(bio, "Unsupported, hex dump follows:\n");
        BIO_dump_indent(bio, (const char *)msg, msglen, indent + 4);
    }
    return 1;
}