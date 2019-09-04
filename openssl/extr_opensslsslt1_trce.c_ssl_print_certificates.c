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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  SSL3_MT_CERTIFICATE ; 
 scalar_t__ SSL_IS_TLS13 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ssl_print_certificate (int /*<<< orphan*/ *,int,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_extensions (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 

__attribute__((used)) static int ssl_print_certificates(BIO *bio, const SSL *ssl, int server,
                                  int indent, const unsigned char *msg,
                                  size_t msglen)
{
    size_t clen;

    if (SSL_IS_TLS13(ssl)
            && !ssl_print_hexbuf(bio, indent, "context", 1, &msg, &msglen))
        return 0;

    if (msglen < 3)
        return 0;
    clen = (msg[0] << 16) | (msg[1] << 8) | msg[2];
    if (msglen != clen + 3)
        return 0;
    msg += 3;
    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "certificate_list, length=%d\n", (int)clen);
    while (clen > 0) {
        if (!ssl_print_certificate(bio, indent + 2, &msg, &clen))
            return 0;
        if (!ssl_print_extensions(bio, indent + 2, server, SSL3_MT_CERTIFICATE,
                                  &msg, &clen))
            return 0;

    }
    return 1;
}