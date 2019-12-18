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
struct nn_bipc {int /*<<< orphan*/  usock; int /*<<< orphan*/ * aipc; int /*<<< orphan*/  fsm; int /*<<< orphan*/  ep; } ;
struct nn_aipc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BIPC_SRC_AIPC ; 
 int /*<<< orphan*/  alloc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_aipc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_aipc_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nn_bipc_start_accepting (struct nn_bipc *self)
{
    nn_assert (self->aipc == NULL);

    /*  Allocate new aipc state machine. */
    self->aipc = nn_alloc (sizeof (struct nn_aipc), "aipc");
    alloc_assert (self->aipc);
    nn_aipc_init (self->aipc, NN_BIPC_SRC_AIPC, self->ep, &self->fsm);

    /*  Start waiting for a new incoming connection. */
    nn_aipc_start (self->aipc, &self->usock);
}