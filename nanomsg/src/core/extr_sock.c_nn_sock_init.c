#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nn_socktype {int flags; int (* create ) (void*,int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {int sndprio; int rcvprio; int ipv4only; } ;
struct nn_sock {int holds; int eid; int sndbuf; int rcvbuf; int rcvmaxsize; int sndtimeo; int rcvtimeo; int reconnect_ivl; int maxttl; int inbuffersz; int outbuffersz; int /*<<< orphan*/  ctx; int /*<<< orphan*/  fsm; struct nn_socktype const* socktype; int /*<<< orphan*/  sockbase; int /*<<< orphan*/ ** optsets; scalar_t__ sec_attr_size; int /*<<< orphan*/ * sec_attr; int /*<<< orphan*/  socket_name; int /*<<< orphan*/  statistics; TYPE_1__ ep_template; scalar_t__ reconnect_ivl_max; int /*<<< orphan*/  sdeps; int /*<<< orphan*/  eps; scalar_t__ flags; int /*<<< orphan*/  sndfd; int /*<<< orphan*/  rcvfd; int /*<<< orphan*/  relesem; int /*<<< orphan*/  termsem; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int NN_MAX_TRANSPORT ; 
 int NN_SOCKTYPE_FLAG_NORECV ; 
 int NN_SOCKTYPE_FLAG_NOSEND ; 
 int /*<<< orphan*/  NN_SOCK_STATE_INIT ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_ctx_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_ctx_leave (int /*<<< orphan*/ *) ; 
 int nn_efd_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_efd_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_global_getpool () ; 
 int /*<<< orphan*/  nn_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sem_init (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_sock_handler ; 
 int /*<<< orphan*/  nn_sock_onleave ; 
 int /*<<< orphan*/  nn_sock_shutdown ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (void*,int /*<<< orphan*/ *) ; 

int nn_sock_init (struct nn_sock *self, const struct nn_socktype *socktype,
    int fd)
{
    int rc;
    int i;

    /* Make sure that at least one message direction is supported. */
    nn_assert (!(socktype->flags & NN_SOCKTYPE_FLAG_NOSEND) ||
        !(socktype->flags & NN_SOCKTYPE_FLAG_NORECV));

    /*  Create the AIO context for the SP socket. */
    nn_ctx_init (&self->ctx, nn_global_getpool (), nn_sock_onleave);

    /*  Initialise the state machine. */
    nn_fsm_init_root (&self->fsm, nn_sock_handler,
        nn_sock_shutdown, &self->ctx);
    self->state = NN_SOCK_STATE_INIT;

    /*  Open the NN_SNDFD and NN_RCVFD efds. Do so, only if the socket type
        supports send/recv, as appropriate. */
    if (socktype->flags & NN_SOCKTYPE_FLAG_NOSEND)
        memset (&self->sndfd, 0xcd, sizeof (self->sndfd));
    else {
        rc = nn_efd_init (&self->sndfd);
        if (nn_slow (rc < 0))
            return rc;
    }
    if (socktype->flags & NN_SOCKTYPE_FLAG_NORECV)
        memset (&self->rcvfd, 0xcd, sizeof (self->rcvfd));
    else {
        rc = nn_efd_init (&self->rcvfd);
        if (nn_slow (rc < 0)) {
            if (!(socktype->flags & NN_SOCKTYPE_FLAG_NOSEND))
                nn_efd_term (&self->sndfd);
            return rc;
        }
    }
    nn_sem_init (&self->termsem);
    nn_sem_init (&self->relesem);
    if (nn_slow (rc < 0)) {
        if (!(socktype->flags & NN_SOCKTYPE_FLAG_NORECV))
            nn_efd_term (&self->rcvfd);
        if (!(socktype->flags & NN_SOCKTYPE_FLAG_NOSEND))
            nn_efd_term (&self->sndfd);
        return rc;
    }

    self->holds = 1;   /*  Callers hold. */
    self->flags = 0;
    nn_list_init (&self->eps);
    nn_list_init (&self->sdeps);
    self->eid = 1;

    /*  Default values for NN_SOL_SOCKET options. */
    self->sndbuf = 128 * 1024;
    self->rcvbuf = 128 * 1024;
    self->rcvmaxsize = 1024 * 1024;
    self->sndtimeo = -1;
    self->rcvtimeo = -1;
    self->reconnect_ivl = 100;
    self->reconnect_ivl_max = 0;
    self->maxttl = 8;
    self->ep_template.sndprio = 8;
    self->ep_template.rcvprio = 8;
    self->ep_template.ipv4only = 1;

    /* Clear statistic entries */
    memset(&self->statistics, 0, sizeof (self->statistics));

    /*  Should be pretty much enough space for just the number  */
    sprintf(self->socket_name, "%d", fd);

    /* Security attribute */
    self->sec_attr = NULL;
    self->sec_attr_size = 0;
    self->inbuffersz = 4096;
    self->outbuffersz = 4096;

    /*  The transport-specific options are not initialised immediately,
        rather, they are allocated later on when needed. */
    for (i = 0; i != NN_MAX_TRANSPORT; ++i)
        self->optsets [i] = NULL;

    /*  Create the specific socket type itself. */
    rc = socktype->create ((void*) self, &self->sockbase);
    errnum_assert (rc == 0, -rc);
    self->socktype = socktype;

    /*  Launch the state machine. */
    nn_ctx_enter (&self->ctx);
    nn_fsm_start (&self->fsm);
    nn_ctx_leave (&self->ctx);

    return 0;
}