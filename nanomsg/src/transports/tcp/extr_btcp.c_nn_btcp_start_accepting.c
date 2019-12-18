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
struct nn_btcp {int /*<<< orphan*/  usock; int /*<<< orphan*/ * atcp; int /*<<< orphan*/  fsm; int /*<<< orphan*/  ep; } ;
struct nn_atcp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BTCP_SRC_ATCP ; 
 int /*<<< orphan*/  alloc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_atcp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_atcp_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_btcp_start_accepting (struct nn_btcp *self)
{
    nn_assert (self->atcp == NULL);

    /*  Allocate new atcp state machine. */
    self->atcp = nn_alloc (sizeof (struct nn_atcp), "atcp");
    alloc_assert (self->atcp);
    nn_atcp_init (self->atcp, NN_BTCP_SRC_ATCP, self->ep, &self->fsm);

    /*  Start waiting for a new incoming connection. */
    nn_atcp_start (self->atcp, &self->usock);
}