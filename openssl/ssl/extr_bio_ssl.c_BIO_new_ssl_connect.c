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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_ssl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_s_connect () ; 

BIO *BIO_new_ssl_connect(SSL_CTX *ctx)
{
#ifndef OPENSSL_NO_SOCK
    BIO *ret = NULL, *con = NULL, *ssl = NULL;

    if ((con = BIO_new(BIO_s_connect())) == NULL)
        return NULL;
    if ((ssl = BIO_new_ssl(ctx, 1)) == NULL)
        goto err;
    if ((ret = BIO_push(ssl, con)) == NULL)
        goto err;
    return ret;
 err:
    BIO_free(con);
#endif
    return NULL;
}