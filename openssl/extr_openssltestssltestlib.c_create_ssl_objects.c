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
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_mem_eof_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_is_dtls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_s_mempacket_test () ; 

int create_ssl_objects(SSL_CTX *serverctx, SSL_CTX *clientctx, SSL **sssl,
                          SSL **cssl, BIO *s_to_c_fbio, BIO *c_to_s_fbio)
{
    SSL *serverssl = NULL, *clientssl = NULL;
    BIO *s_to_c_bio = NULL, *c_to_s_bio = NULL;

    if (*sssl != NULL)
        serverssl = *sssl;
    else if (!TEST_ptr(serverssl = SSL_new(serverctx)))
        goto error;
    if (*cssl != NULL)
        clientssl = *cssl;
    else if (!TEST_ptr(clientssl = SSL_new(clientctx)))
        goto error;

    if (SSL_is_dtls(clientssl)) {
        if (!TEST_ptr(s_to_c_bio = BIO_new(bio_s_mempacket_test()))
                || !TEST_ptr(c_to_s_bio = BIO_new(bio_s_mempacket_test())))
            goto error;
    } else {
        if (!TEST_ptr(s_to_c_bio = BIO_new(BIO_s_mem()))
                || !TEST_ptr(c_to_s_bio = BIO_new(BIO_s_mem())))
            goto error;
    }

    if (s_to_c_fbio != NULL
            && !TEST_ptr(s_to_c_bio = BIO_push(s_to_c_fbio, s_to_c_bio)))
        goto error;
    if (c_to_s_fbio != NULL
            && !TEST_ptr(c_to_s_bio = BIO_push(c_to_s_fbio, c_to_s_bio)))
        goto error;

    /* Set Non-blocking IO behaviour */
    BIO_set_mem_eof_return(s_to_c_bio, -1);
    BIO_set_mem_eof_return(c_to_s_bio, -1);

    /* Up ref these as we are passing them to two SSL objects */
    SSL_set_bio(serverssl, c_to_s_bio, s_to_c_bio);
    BIO_up_ref(s_to_c_bio);
    BIO_up_ref(c_to_s_bio);
    SSL_set_bio(clientssl, s_to_c_bio, c_to_s_bio);
    *sssl = serverssl;
    *cssl = clientssl;
    return 1;

 error:
    SSL_free(serverssl);
    SSL_free(clientssl);
    BIO_free(s_to_c_bio);
    BIO_free(c_to_s_bio);
    BIO_free(s_to_c_fbio);
    BIO_free(c_to_s_fbio);

    return 0;
}