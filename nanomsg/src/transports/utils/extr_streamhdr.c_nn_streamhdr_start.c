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
typedef  int /*<<< orphan*/  uint16_t ;
struct nn_usock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fsm; int /*<<< orphan*/  src; } ;
struct nn_streamhdr {int /*<<< orphan*/  fsm; scalar_t__ protohdr; struct nn_pipebase* pipebase; struct nn_usock* usock; TYPE_1__ usock_owner; } ;
struct nn_pipebase {int dummy; } ;
typedef  int /*<<< orphan*/  protocol ;

/* Variables and functions */
 int /*<<< orphan*/  NN_PROTOCOL ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  NN_STREAMHDR_SRC_USOCK ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_pipebase_getopt (struct nn_pipebase*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  nn_puts (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_usock_swap_owner (struct nn_usock*,TYPE_1__*) ; 

void nn_streamhdr_start (struct nn_streamhdr *self, struct nn_usock *usock,
    struct nn_pipebase *pipebase)
{
    size_t sz;
    int protocol;

    /*  Take ownership of the underlying socket. */
    nn_assert (self->usock == NULL && self->usock_owner.fsm == NULL);
    self->usock_owner.src = NN_STREAMHDR_SRC_USOCK;
    self->usock_owner.fsm = &self->fsm;
    nn_usock_swap_owner (usock, &self->usock_owner);
    self->usock = usock;
    self->pipebase = pipebase;

    /*  Get the protocol identifier. */
    sz = sizeof (protocol);
    nn_pipebase_getopt (pipebase, NN_SOL_SOCKET, NN_PROTOCOL, &protocol, &sz);
    nn_assert (sz == sizeof (protocol));

    /*  Compose the protocol header. */
    memcpy (self->protohdr, "\0SP\0\0\0\0\0", 8);
    nn_puts (self->protohdr + 4, (uint16_t) protocol);

    /*  Launch the state machine. */
    nn_fsm_start (&self->fsm);
}