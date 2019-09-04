#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int shutdown; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_DGRAM_SCTP_SAVE_SHUTDOWN ; 
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_dgram_is_sctp (int /*<<< orphan*/ *) ; 
 int BIO_dgram_sctp_wait_for_dry (int /*<<< orphan*/ *) ; 
 int SSL_SENT_SHUTDOWN ; 
 int /*<<< orphan*/ * SSL_get_wbio (TYPE_1__*) ; 
 int ssl3_shutdown (TYPE_1__*) ; 

int dtls1_shutdown(SSL *s)
{
    int ret;
#ifndef OPENSSL_NO_SCTP
    BIO *wbio;

    wbio = SSL_get_wbio(s);
    if (wbio != NULL && BIO_dgram_is_sctp(wbio) &&
        !(s->shutdown & SSL_SENT_SHUTDOWN)) {
        ret = BIO_dgram_sctp_wait_for_dry(wbio);
        if (ret < 0)
            return -1;

        if (ret == 0)
            BIO_ctrl(SSL_get_wbio(s), BIO_CTRL_DGRAM_SCTP_SAVE_SHUTDOWN, 1,
                     NULL);
    }
#endif
    ret = ssl3_shutdown(s);
#ifndef OPENSSL_NO_SCTP
    BIO_ctrl(SSL_get_wbio(s), BIO_CTRL_DGRAM_SCTP_SAVE_SHUTDOWN, 0, NULL);
#endif
    return ret;
}