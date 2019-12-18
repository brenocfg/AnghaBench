#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* d1; } ;
struct TYPE_7__ {scalar_t__ link_mtu; scalar_t__ mtu; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_DGRAM_QUERY_MTU ; 
 int /*<<< orphan*/  BIO_CTRL_DGRAM_SET_MTU ; 
 scalar_t__ BIO_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_dgram_get_mtu_overhead (int /*<<< orphan*/ ) ; 
 int SSL_OP_NO_QUERY_MTU ; 
 int SSL_get_options (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_get_wbio (TYPE_2__*) ; 
 scalar_t__ dtls1_min_mtu (TYPE_2__*) ; 

int dtls1_query_mtu(SSL *s)
{
    if (s->d1->link_mtu) {
        s->d1->mtu =
            s->d1->link_mtu - BIO_dgram_get_mtu_overhead(SSL_get_wbio(s));
        s->d1->link_mtu = 0;
    }

    /* AHA!  Figure out the MTU, and stick to the right size */
    if (s->d1->mtu < dtls1_min_mtu(s)) {
        if (!(SSL_get_options(s) & SSL_OP_NO_QUERY_MTU)) {
            s->d1->mtu =
                BIO_ctrl(SSL_get_wbio(s), BIO_CTRL_DGRAM_QUERY_MTU, 0, NULL);

            /*
             * I've seen the kernel return bogus numbers when it doesn't know
             * (initial write), so just make sure we have a reasonable number
             */
            if (s->d1->mtu < dtls1_min_mtu(s)) {
                /* Set to min mtu */
                s->d1->mtu = dtls1_min_mtu(s);
                BIO_ctrl(SSL_get_wbio(s), BIO_CTRL_DGRAM_SET_MTU,
                         (long)s->d1->mtu, NULL);
            }
        } else
            return 0;
    }
    return 1;
}