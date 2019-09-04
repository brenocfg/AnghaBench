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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ SSL_USE_SIGALGS (int /*<<< orphan*/  const*) ; 
 int ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_sigalg_tbl ; 
 int /*<<< orphan*/  ssl_trace_str (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_print_signature(BIO *bio, int indent, const SSL *ssl,
                               const unsigned char **pmsg, size_t *pmsglen)
{
    if (*pmsglen < 2)
        return 0;
    if (SSL_USE_SIGALGS(ssl)) {
        const unsigned char *p = *pmsg;
        unsigned int sigalg = (p[0] << 8) | p[1];

        BIO_indent(bio, indent, 80);
        BIO_printf(bio, "Signature Algorithm: %s (0x%04x)\n",
                   ssl_trace_str(sigalg, ssl_sigalg_tbl), sigalg);
        *pmsg += 2;
        *pmsglen -= 2;
    }
    return ssl_print_hexbuf(bio, indent, "Signature", 2, pmsg, pmsglen);
}