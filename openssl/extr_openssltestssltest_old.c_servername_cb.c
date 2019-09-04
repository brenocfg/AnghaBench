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

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 char* SSL_get_servername (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_SSL_CTX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLSEXT_NAMETYPE_host_name ; 
 int /*<<< orphan*/  bio_stdout ; 
 int /*<<< orphan*/ * s_ctx2 ; 
 int /*<<< orphan*/ * sn_server2 ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int servername_cb(SSL *s, int *ad, void *arg)
{
    const char *servername = SSL_get_servername(s, TLSEXT_NAMETYPE_host_name);
    if (sn_server2 == NULL) {
        BIO_printf(bio_stdout, "Servername 2 is NULL\n");
        return SSL_TLSEXT_ERR_NOACK;
    }

    if (servername) {
        if (s_ctx2 != NULL && sn_server2 != NULL &&
            !strcasecmp(servername, sn_server2)) {
            BIO_printf(bio_stdout, "Switching server context.\n");
            SSL_set_SSL_CTX(s, s_ctx2);
        }
    }
    return SSL_TLSEXT_ERR_OK;
}