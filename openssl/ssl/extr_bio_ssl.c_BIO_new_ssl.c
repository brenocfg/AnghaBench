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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLOSE ; 
 int /*<<< orphan*/  BIO_f_ssl () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 

BIO *BIO_new_ssl(SSL_CTX *ctx, int client)
{
    BIO *ret;
    SSL *ssl;

    if ((ret = BIO_new(BIO_f_ssl())) == NULL)
        return NULL;
    if ((ssl = SSL_new(ctx)) == NULL) {
        BIO_free(ret);
        return NULL;
    }
    if (client)
        SSL_set_connect_state(ssl);
    else
        SSL_set_accept_state(ssl);

    BIO_set_ssl(ret, ssl, BIO_CLOSE);
    return ret;
}