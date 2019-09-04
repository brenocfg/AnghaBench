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

/* Variables and functions */
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  SSL_check_private_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_SSL_CTX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_use_PrivateKey_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_use_certificate_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cert ; 
 int cert_cb_cnt ; 
 int /*<<< orphan*/  privkey ; 

__attribute__((used)) static int cert_cb(SSL *s, void *arg)
{
    SSL_CTX *ctx = (SSL_CTX *)arg;

    if (cert_cb_cnt == 0) {
        /* Suspend the handshake */
        cert_cb_cnt++;
        return -1;
    } else if (cert_cb_cnt == 1) {
        /*
         * Update the SSL_CTX, set the certificate and private key and then
         * continue the handshake normally.
         */
        if (ctx != NULL && !TEST_ptr(SSL_set_SSL_CTX(s, ctx)))
            return 0;

        if (!TEST_true(SSL_use_certificate_file(s, cert, SSL_FILETYPE_PEM))
                || !TEST_true(SSL_use_PrivateKey_file(s, privkey,
                                                      SSL_FILETYPE_PEM))
                || !TEST_true(SSL_check_private_key(s)))
            return 0;
        cert_cb_cnt++;
        return 1;
    }

    /* Abort the handshake */
    return 0;
}