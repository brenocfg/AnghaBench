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
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_SSL_USE_RSAPRIVATEKEY_ASN1 ; 
 int SSL_use_RSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_RSAPrivateKey (int /*<<< orphan*/ *,unsigned char const**,long) ; 

int SSL_use_RSAPrivateKey_ASN1(SSL *ssl, const unsigned char *d, long len)
{
    int ret;
    const unsigned char *p;
    RSA *rsa;

    p = d;
    if ((rsa = d2i_RSAPrivateKey(NULL, &p, (long)len)) == NULL) {
        SSLerr(SSL_F_SSL_USE_RSAPRIVATEKEY_ASN1, ERR_R_ASN1_LIB);
        return 0;
    }

    ret = SSL_use_RSAPrivateKey(ssl, rsa);
    RSA_free(rsa);
    return ret;
}