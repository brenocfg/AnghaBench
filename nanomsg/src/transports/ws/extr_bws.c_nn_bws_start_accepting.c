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
struct nn_bws {int /*<<< orphan*/  usock; int /*<<< orphan*/ * aws; int /*<<< orphan*/  fsm; int /*<<< orphan*/  ep; } ;
struct nn_aws {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_BWS_SRC_AWS ; 
 int /*<<< orphan*/  alloc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_aws_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_aws_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_bws_start_accepting (struct nn_bws *self)
{
    nn_assert (self->aws == NULL);

    /*  Allocate new aws state machine. */
    self->aws = nn_alloc (sizeof (struct nn_aws), "aws");
    alloc_assert (self->aws);
    nn_aws_init (self->aws, NN_BWS_SRC_AWS, self->ep, &self->fsm);

    /*  Start waiting for a new incoming connection. */
    nn_aws_start (self->aws, &self->usock);
}