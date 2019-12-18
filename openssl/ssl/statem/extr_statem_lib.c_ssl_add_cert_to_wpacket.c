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
typedef  int /*<<< orphan*/  WPACKET ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_3_CERTIFICATE ; 
 int /*<<< orphan*/  SSL_F_SSL_ADD_CERT_TO_WPACKET ; 
 scalar_t__ SSL_IS_TLS13 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_allocate_bytes_u24 (int /*<<< orphan*/ *,int,unsigned char**) ; 
 int i2d_X509 (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  tls_construct_extensions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ssl_add_cert_to_wpacket(SSL *s, WPACKET *pkt, X509 *x, int chain)
{
    int len;
    unsigned char *outbytes;

    len = i2d_X509(x, NULL);
    if (len < 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_ADD_CERT_TO_WPACKET,
                 ERR_R_BUF_LIB);
        return 0;
    }
    if (!WPACKET_sub_allocate_bytes_u24(pkt, len, &outbytes)
            || i2d_X509(x, &outbytes) != len) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_ADD_CERT_TO_WPACKET,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (SSL_IS_TLS13(s)
            && !tls_construct_extensions(s, pkt, SSL_EXT_TLS1_3_CERTIFICATE, x,
                                         chain)) {
        /* SSLfatal() already called */
        return 0;
    }

    return 1;
}