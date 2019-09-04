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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL_AD_INTERNAL_ERROR ; 
 unsigned int SSL_EXT_TLS1_3_CERTIFICATE ; 
 int serverinfo_find_extension (unsigned char const*,size_t,unsigned int,unsigned char const**,size_t*) ; 
 scalar_t__ ssl_get_server_cert_serverinfo (int /*<<< orphan*/ *,unsigned char const**,size_t*) ; 

__attribute__((used)) static int serverinfoex_srv_add_cb(SSL *s, unsigned int ext_type,
                                   unsigned int context,
                                   const unsigned char **out,
                                   size_t *outlen, X509 *x, size_t chainidx,
                                   int *al, void *arg)
{
    const unsigned char *serverinfo = NULL;
    size_t serverinfo_length = 0;

    /* We only support extensions for the first Certificate */
    if ((context & SSL_EXT_TLS1_3_CERTIFICATE) != 0 && chainidx > 0)
        return 0;

    /* Is there serverinfo data for the chosen server cert? */
    if ((ssl_get_server_cert_serverinfo(s, &serverinfo,
                                        &serverinfo_length)) != 0) {
        /* Find the relevant extension from the serverinfo */
        int retval = serverinfo_find_extension(serverinfo, serverinfo_length,
                                               ext_type, out, outlen);
        if (retval == -1) {
            *al = SSL_AD_INTERNAL_ERROR;
            return -1;          /* Error */
        }
        if (retval == 0)
            return 0;           /* No extension found, don't send extension */
        return 1;               /* Send extension */
    }
    return 0;                   /* No serverinfo data found, don't send
                                 * extension */
}