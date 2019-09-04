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
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL3_MT_CERTIFICATE_REQUEST ; 
 scalar_t__ SSL_IS_TLS13 (int /*<<< orphan*/  const*) ; 
 scalar_t__ SSL_USE_SIGALGS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XN_FLAG_ONELINE ; 
 int /*<<< orphan*/ * d2i_X509_NAME (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int /*<<< orphan*/  ssl_ctype_tbl ; 
 int /*<<< orphan*/  ssl_print_extensions (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_print_hexbuf (int /*<<< orphan*/ *,int,char*,int,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ssl_sigalg_tbl ; 
 int /*<<< orphan*/  ssl_trace_list (int /*<<< orphan*/ *,int,unsigned char const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_trace_str (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_print_cert_request(BIO *bio, int indent, const SSL *ssl,
                                  const unsigned char *msg, size_t msglen)
{
    size_t xlen;
    unsigned int sigalg;

    if (SSL_IS_TLS13(ssl)) {
        if (!ssl_print_hexbuf(bio, indent, "request_context", 1, &msg, &msglen))
            return 0;
        if (!ssl_print_extensions(bio, indent, 1,
                                  SSL3_MT_CERTIFICATE_REQUEST, &msg, &msglen))
            return 0;
        return 1;
    } else {
        if (msglen < 1)
            return 0;
        xlen = msg[0];
        if (msglen < xlen + 1)
            return 0;
        msg++;
        BIO_indent(bio, indent, 80);
        BIO_printf(bio, "certificate_types (len=%d)\n", (int)xlen);
        if (!ssl_trace_list(bio, indent + 2, msg, xlen, 1, ssl_ctype_tbl))
            return 0;
        msg += xlen;
        msglen -= xlen + 1;
    }
    if (SSL_USE_SIGALGS(ssl)) {
        if (msglen < 2)
            return 0;
        xlen = (msg[0] << 8) | msg[1];
        if (msglen < xlen + 2 || (xlen & 1))
            return 0;
        msg += 2;
        msglen -= xlen + 2;
        BIO_indent(bio, indent, 80);
        BIO_printf(bio, "signature_algorithms (len=%d)\n", (int)xlen);
        while (xlen > 0) {
            BIO_indent(bio, indent + 2, 80);
            sigalg = (msg[0] << 8) | msg[1];
            BIO_printf(bio, "%s (0x%04x)\n",
                       ssl_trace_str(sigalg, ssl_sigalg_tbl), sigalg);
            xlen -= 2;
            msg += 2;
        }
        msg += xlen;
    }

    if (msglen < 2)
        return 0;
    xlen = (msg[0] << 8) | msg[1];
    BIO_indent(bio, indent, 80);
    if (msglen < xlen + 2)
        return 0;
    msg += 2;
    msglen -= 2 + xlen;
    BIO_printf(bio, "certificate_authorities (len=%d)\n", (int)xlen);
    while (xlen > 0) {
        size_t dlen;
        X509_NAME *nm;
        const unsigned char *p;
        if (xlen < 2)
            return 0;
        dlen = (msg[0] << 8) | msg[1];
        if (xlen < dlen + 2)
            return 0;
        msg += 2;
        BIO_indent(bio, indent + 2, 80);
        BIO_printf(bio, "DistinguishedName (len=%d): ", (int)dlen);
        p = msg;
        nm = d2i_X509_NAME(NULL, &p, dlen);
        if (!nm) {
            BIO_puts(bio, "<UNPARSEABLE DN>\n");
        } else {
            X509_NAME_print_ex(bio, nm, 0, XN_FLAG_ONELINE);
            BIO_puts(bio, "\n");
            X509_NAME_free(nm);
        }
        xlen -= dlen + 2;
        msg += dlen;
    }
    if (SSL_IS_TLS13(ssl)) {
        if (!ssl_print_hexbuf(bio, indent, "request_extensions", 2,
                              &msg, &msglen))
            return 0;
    }
    return msglen == 0;
}