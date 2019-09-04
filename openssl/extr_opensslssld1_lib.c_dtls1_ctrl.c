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
struct timeval {int dummy; } ;
struct TYPE_8__ {TYPE_1__* d1; } ;
struct TYPE_7__ {long link_mtu; long mtu; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  DTLS1_MAX_MTU_OVERHEAD ; 
#define  DTLS_CTRL_GET_LINK_MIN_MTU 132 
#define  DTLS_CTRL_GET_TIMEOUT 131 
#define  DTLS_CTRL_HANDLE_TIMEOUT 130 
#define  DTLS_CTRL_SET_LINK_MTU 129 
#define  SSL_CTRL_SET_MTU 128 
 int /*<<< orphan*/ * dtls1_get_timeout (TYPE_2__*,struct timeval*) ; 
 int dtls1_handle_timeout (TYPE_2__*) ; 
 scalar_t__ dtls1_link_min_mtu () ; 
 int ssl3_ctrl (TYPE_2__*,int,long,void*) ; 

long dtls1_ctrl(SSL *s, int cmd, long larg, void *parg)
{
    int ret = 0;

    switch (cmd) {
    case DTLS_CTRL_GET_TIMEOUT:
        if (dtls1_get_timeout(s, (struct timeval *)parg) != NULL) {
            ret = 1;
        }
        break;
    case DTLS_CTRL_HANDLE_TIMEOUT:
        ret = dtls1_handle_timeout(s);
        break;
    case DTLS_CTRL_SET_LINK_MTU:
        if (larg < (long)dtls1_link_min_mtu())
            return 0;
        s->d1->link_mtu = larg;
        return 1;
    case DTLS_CTRL_GET_LINK_MIN_MTU:
        return (long)dtls1_link_min_mtu();
    case SSL_CTRL_SET_MTU:
        /*
         *  We may not have a BIO set yet so can't call dtls1_min_mtu()
         *  We'll have to make do with dtls1_link_min_mtu() and max overhead
         */
        if (larg < (long)dtls1_link_min_mtu() - DTLS1_MAX_MTU_OVERHEAD)
            return 0;
        s->d1->mtu = larg;
        return larg;
    default:
        ret = ssl3_ctrl(s, cmd, larg, parg);
        break;
    }
    return ret;
}