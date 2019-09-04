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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_socket () ; 
 int /*<<< orphan*/  BIO_set_fd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  SSL_F_SSL_SET_FD ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktls_enable (int) ; 

int SSL_set_fd(SSL *s, int fd)
{
    int ret = 0;
    BIO *bio = NULL;

    bio = BIO_new(BIO_s_socket());

    if (bio == NULL) {
        SSLerr(SSL_F_SSL_SET_FD, ERR_R_BUF_LIB);
        goto err;
    }
    BIO_set_fd(bio, fd, BIO_NOCLOSE);
    SSL_set_bio(s, bio, bio);
#ifndef OPENSSL_NO_KTLS
    /*
     * The new socket is created successfully regardless of ktls_enable.
     * ktls_enable doesn't change any functionality of the socket, except
     * changing the setsockopt to enable the processing of ktls_start.
     * Thus, it is not a problem to call it for non-TLS sockets.
     */
    ktls_enable(fd);
#endif /* OPENSSL_NO_KTLS */
    ret = 1;
 err:
    return ret;
}