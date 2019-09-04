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

/* Variables and functions */
 int /*<<< orphan*/  BIO_FLAGS_READ ; 
 int /*<<< orphan*/  BIO_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DTLS1_READ_FAILED ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_in_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dtls1_handle_timeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtls1_is_timer_expired (int /*<<< orphan*/ *) ; 
 scalar_t__ ossl_statem_in_error (int /*<<< orphan*/ *) ; 

int dtls1_read_failed(SSL *s, int code)
{
    if (code > 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_DTLS1_READ_FAILED, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (!dtls1_is_timer_expired(s) || ossl_statem_in_error(s)) {
        /*
         * not a timeout, none of our business, let higher layers handle
         * this.  in fact it's probably an error
         */
        return code;
    }
    /* done, no need to send a retransmit */
    if (!SSL_in_init(s))
    {
        BIO_set_flags(SSL_get_rbio(s), BIO_FLAGS_READ);
        return code;
    }

    return dtls1_handle_timeout(s);
}