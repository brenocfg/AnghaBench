#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int extension_error; int /*<<< orphan*/ * biodebug; int /*<<< orphan*/ * servername; } ;
typedef  TYPE_1__ tlsextctx ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 char* SSL_get_servername (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_SSL_CTX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLSEXT_NAMETYPE_host_name ; 
 int /*<<< orphan*/ * ctx2 ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isprint (unsigned char) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_servername_cb(SSL *s, int *ad, void *arg)
{
    tlsextctx *p = (tlsextctx *) arg;
    const char *servername = SSL_get_servername(s, TLSEXT_NAMETYPE_host_name);

    if (servername != NULL && p->biodebug != NULL) {
        const char *cp = servername;
        unsigned char uc;

        BIO_printf(p->biodebug, "Hostname in TLS extension: \"");
        while ((uc = *cp++) != 0)
            BIO_printf(p->biodebug,
                       isascii(uc) && isprint(uc) ? "%c" : "\\x%02x", uc);
        BIO_printf(p->biodebug, "\"\n");
    }

    if (p->servername == NULL)
        return SSL_TLSEXT_ERR_NOACK;

    if (servername != NULL) {
        if (strcasecmp(servername, p->servername))
            return p->extension_error;
        if (ctx2 != NULL) {
            BIO_printf(p->biodebug, "Switching server context.\n");
            SSL_set_SSL_CTX(s, ctx2);
        }
    }
    return SSL_TLSEXT_ERR_OK;
}