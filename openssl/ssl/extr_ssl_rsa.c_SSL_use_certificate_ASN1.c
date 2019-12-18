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
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  SSL_F_SSL_USE_CERTIFICATE_ASN1 ; 
 int SSL_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509 (int /*<<< orphan*/ *,unsigned char const**,long) ; 

int SSL_use_certificate_ASN1(SSL *ssl, const unsigned char *d, int len)
{
    X509 *x;
    int ret;

    x = d2i_X509(NULL, &d, (long)len);
    if (x == NULL) {
        SSLerr(SSL_F_SSL_USE_CERTIFICATE_ASN1, ERR_R_ASN1_LIB);
        return 0;
    }

    ret = SSL_use_certificate(ssl, x);
    X509_free(x);
    return ret;
}