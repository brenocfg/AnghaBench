#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* d1; } ;
struct TYPE_8__ {int num_alerts; } ;
struct TYPE_9__ {size_t mtu; TYPE_1__ timeout; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_DGRAM_GET_FALLBACK_MTU ; 
 size_t BIO_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DTLS1_TMO_ALERT_COUNT ; 
 int /*<<< orphan*/  SSL_AD_NO_ALERT ; 
 int SSL_OP_NO_QUERY_MTU ; 
 int /*<<< orphan*/  SSL_R_READ_TIMEOUT_EXPIRED ; 
 int SSL_get_options (TYPE_3__*) ; 
 int /*<<< orphan*/  SSL_get_wbio (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dtls1_check_timeout_num(SSL *s)
{
    size_t mtu;

    s->d1->timeout.num_alerts++;

    /* Reduce MTU after 2 unsuccessful retransmissions */
    if (s->d1->timeout.num_alerts > 2
        && !(SSL_get_options(s) & SSL_OP_NO_QUERY_MTU)) {
        mtu =
            BIO_ctrl(SSL_get_wbio(s), BIO_CTRL_DGRAM_GET_FALLBACK_MTU, 0, NULL);
        if (mtu < s->d1->mtu)
            s->d1->mtu = mtu;
    }

    if (s->d1->timeout.num_alerts > DTLS1_TMO_ALERT_COUNT) {
        /* fail the connection, enough alerts have been sent */
        SSLfatal(s, SSL_AD_NO_ALERT, 0,
                 SSL_R_READ_TIMEOUT_EXPIRED);
        return -1;
    }

    return 0;
}