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
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL3_MT_NEWSESSION_TICKET ; 
 scalar_t__ SSL_IS_TLS13 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ssl_print_extensions (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 

__attribute__((used)) static int ssl_print_ticket(BIO *bio, int indent, const SSL *ssl,
                            const unsigned char *msg, size_t msglen)
{
    unsigned int tick_life;

    if (msglen == 0) {
        BIO_indent(bio, indent + 2, 80);
        BIO_puts(bio, "No Ticket\n");
        return 1;
    }
    if (msglen < 4)
        return 0;
    tick_life = (msg[0] << 24) | (msg[1] << 16) | (msg[2] << 8) | msg[3];
    msglen -= 4;
    msg += 4;
    BIO_indent(bio, indent + 2, 80);
    BIO_printf(bio, "ticket_lifetime_hint=%u\n", tick_life);
    if (SSL_IS_TLS13(ssl)) {
        unsigned int ticket_age_add;

        if (msglen < 4)
            return 0;
        ticket_age_add =
            (msg[0] << 24) | (msg[1] << 16) | (msg[2] << 8) | msg[3];
        msglen -= 4;
        msg += 4;
        BIO_indent(bio, indent + 2, 80);
        BIO_printf(bio, "ticket_age_add=%u\n", ticket_age_add);
        if (!ssl_print_hexbuf(bio, indent + 2, "ticket_nonce", 1, &msg,
                              &msglen))
            return 0;
    }
    if (!ssl_print_hexbuf(bio, indent + 2, "ticket", 2, &msg, &msglen))
        return 0;
    if (SSL_IS_TLS13(ssl)
            && !ssl_print_extensions(bio, indent + 2, 0,
                                     SSL3_MT_NEWSESSION_TICKET, &msg, &msglen))
        return 0;
    if (msglen)
        return 0;
    return 1;
}