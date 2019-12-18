#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int sndprio; int rcvprio; int ipv4only; } ;
struct nn_sock {int sndbuf; int rcvbuf; int rcvmaxsize; int sndtimeo; int rcvtimeo; int reconnect_ivl; int reconnect_ivl_max; int maxttl; TYPE_3__ ep_template; scalar_t__* socket_name; TYPE_4__* sockbase; } ;
struct nn_optset {TYPE_2__* vfptr; } ;
struct TYPE_8__ {TYPE_1__* vfptr; } ;
struct TYPE_6__ {int (* setopt ) (struct nn_optset*,int,void const*,size_t) ;} ;
struct TYPE_5__ {int (* setopt ) (TYPE_4__*,int,int,void const*,size_t) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
#define  NN_IPV4ONLY 139 
#define  NN_LINGER 138 
#define  NN_MAXTTL 137 
#define  NN_RCVBUF 136 
#define  NN_RCVMAXSIZE 135 
#define  NN_RCVPRIO 134 
#define  NN_RCVTIMEO 133 
#define  NN_RECONNECT_IVL 132 
#define  NN_RECONNECT_IVL_MAX 131 
#define  NN_SNDBUF 130 
#define  NN_SNDPRIO 129 
#define  NN_SNDTIMEO 128 
 int NN_SOCKET_NAME ; 
 int NN_SOL_SOCKET ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void const*,size_t) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 struct nn_optset* nn_sock_optset (struct nn_sock*,int) ; 
 int stub1 (TYPE_4__*,int,int,void const*,size_t) ; 
 int stub2 (struct nn_optset*,int,void const*,size_t) ; 

__attribute__((used)) static int nn_sock_setopt_inner (struct nn_sock *self, int level,
    int option, const void *optval, size_t optvallen)
{
    struct nn_optset *optset;
    int val;

    /*  Protocol-specific socket options. */
    if (level > NN_SOL_SOCKET) {
        if (self->sockbase->vfptr->setopt == NULL) {
            return -ENOPROTOOPT;
        }
        return self->sockbase->vfptr->setopt (self->sockbase, level, option,
            optval, optvallen);
    }

    /*  Transport-specific options. */
    if (level < NN_SOL_SOCKET) {
        optset = nn_sock_optset (self, level);
        if (!optset)
            return -ENOPROTOOPT;
        return optset->vfptr->setopt (optset, option, optval, optvallen);
    }

    nn_assert (level == NN_SOL_SOCKET);

    /*  Special-casing socket name for now as it's the only string option  */
    if (option == NN_SOCKET_NAME) {
        if (optvallen > 63)
            return -EINVAL;
        memcpy (self->socket_name, optval, optvallen);
        self->socket_name [optvallen] = 0;
        return 0;
    }

    /*  At this point we assume that all options are of type int. */
    if (optvallen != sizeof (int))
        return -EINVAL;
    val = *(int*) optval;

    /*  Generic socket-level options. */
    switch (option) {
    case NN_SNDBUF:
        if (val <= 0)
            return -EINVAL;
        self->sndbuf = val;
        return 0;
    case NN_RCVBUF:
        if (val <= 0)
            return -EINVAL;
        self->rcvbuf = val;
        return 0;
    case NN_RCVMAXSIZE:
        if (val < -1)
            return -EINVAL;
        self->rcvmaxsize = val;
        return 0;
    case NN_SNDTIMEO:
        self->sndtimeo = val;
        return 0;
    case NN_RCVTIMEO:
        self->rcvtimeo = val;
        return 0;
    case NN_RECONNECT_IVL:
        if (val < 0)
            return -EINVAL;
        self->reconnect_ivl = val;
        return 0;
    case NN_RECONNECT_IVL_MAX:
        if (val < 0)
            return -EINVAL;
        self->reconnect_ivl_max = val;
        return 0;
    case NN_SNDPRIO:
        if (val < 1 || val > 16)
            return -EINVAL;
        self->ep_template.sndprio = val;
        return 0;
    case NN_RCVPRIO:
        if (val < 1 || val > 16)
            return -EINVAL;
        self->ep_template.rcvprio = val;
        return 0;
    case NN_IPV4ONLY:
        if (val != 0 && val != 1)
            return -EINVAL;
        self->ep_template.ipv4only = val;
        return 0;
    case NN_MAXTTL:
        if (val < 1 || val > 255)
            return -EINVAL;
        self->maxttl = val;
        return 0;
    case NN_LINGER:
	/*  Ignored, retained for compatibility. */
        return 0;
    }

    return -ENOPROTOOPT;
}