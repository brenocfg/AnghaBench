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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int EVP_PKEY_security_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 int ssl_ctx_security (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ssl_security (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_security_cert_key(SSL *s, SSL_CTX *ctx, X509 *x, int op)
{
    int secbits = -1;
    EVP_PKEY *pkey = X509_get0_pubkey(x);
    if (pkey) {
        /*
         * If no parameters this will return -1 and fail using the default
         * security callback for any non-zero security level. This will
         * reject keys which omit parameters but this only affects DSA and
         * omission of parameters is never (?) done in practice.
         */
        secbits = EVP_PKEY_security_bits(pkey);
    }
    if (s)
        return ssl_security(s, op, secbits, 0, x);
    else
        return ssl_ctx_security(ctx, op, secbits, 0, x);
}