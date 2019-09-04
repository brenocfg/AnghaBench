#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  DTLS1_RT_HEADER_LENGTH ; 
#define  SSL3_RT_ALERT 132 
#define  SSL3_RT_CHANGE_CIPHER_SPEC 131 
#define  SSL3_RT_HANDSHAKE 130 
#define  SSL3_RT_HEADER 129 
 int /*<<< orphan*/  SSL3_RT_HEADER_LENGTH ; 
#define  SSL3_RT_INNER_CONTENT_TYPE 128 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_1__*) ; 
 unsigned char const SSL_alert_desc_string_long (unsigned char const) ; 
 unsigned char const SSL_alert_type_string_long (unsigned char const) ; 
 int /*<<< orphan*/  ssl_content_tbl ; 
 int /*<<< orphan*/  ssl_print_handshake (int /*<<< orphan*/ *,TYPE_1__*,int,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  ssl_print_hex (int /*<<< orphan*/ *,int,char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_trace_str (unsigned char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_version_tbl ; 

void SSL_trace(int write_p, int version, int content_type,
               const void *buf, size_t msglen, SSL *ssl, void *arg)
{
    const unsigned char *msg = buf;
    BIO *bio = arg;

    switch (content_type) {
    case SSL3_RT_HEADER:
        {
            int hvers;

            /* avoid overlapping with length at the end of buffer */
            if (msglen < (size_t)(SSL_IS_DTLS(ssl) ?
                     DTLS1_RT_HEADER_LENGTH : SSL3_RT_HEADER_LENGTH)) {
                BIO_puts(bio, write_p ? "Sent" : "Received");
                ssl_print_hex(bio, 0, " too short message", msg, msglen);
                break;
            }
            hvers = msg[1] << 8 | msg[2];
            BIO_puts(bio, write_p ? "Sent" : "Received");
            BIO_printf(bio, " Record\nHeader:\n  Version = %s (0x%x)\n",
                       ssl_trace_str(hvers, ssl_version_tbl), hvers);
            if (SSL_IS_DTLS(ssl)) {
                BIO_printf(bio,
                           "  epoch=%d, sequence_number=%04x%04x%04x\n",
                           (msg[3] << 8 | msg[4]),
                           (msg[5] << 8 | msg[6]),
                           (msg[7] << 8 | msg[8]), (msg[9] << 8 | msg[10]));
            }

            BIO_printf(bio, "  Content Type = %s (%d)\n  Length = %d",
                       ssl_trace_str(msg[0], ssl_content_tbl), msg[0],
                       msg[msglen - 2] << 8 | msg[msglen - 1]);
        }
        break;

    case SSL3_RT_INNER_CONTENT_TYPE:
        BIO_printf(bio, "  Inner Content Type = %s (%d)",
                   ssl_trace_str(msg[0], ssl_content_tbl), msg[0]);
        break;

    case SSL3_RT_HANDSHAKE:
        if (!ssl_print_handshake(bio, ssl, ssl->server ? write_p : !write_p,
                                 msg, msglen, 4))
            BIO_printf(bio, "Message length parse error!\n");
        break;

    case SSL3_RT_CHANGE_CIPHER_SPEC:
        if (msglen == 1 && msg[0] == 1)
            BIO_puts(bio, "    change_cipher_spec (1)\n");
        else
            ssl_print_hex(bio, 4, "unknown value", msg, msglen);
        break;

    case SSL3_RT_ALERT:
        if (msglen != 2)
            BIO_puts(bio, "    Illegal Alert Length\n");
        else {
            BIO_printf(bio, "    Level=%s(%d), description=%s(%d)\n",
                       SSL_alert_type_string_long(msg[0] << 8),
                       msg[0], SSL_alert_desc_string_long(msg[1]), msg[1]);
        }

    }

    BIO_puts(bio, "\n");
}