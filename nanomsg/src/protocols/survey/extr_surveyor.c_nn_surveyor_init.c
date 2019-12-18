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
struct TYPE_2__ {int /*<<< orphan*/  sockbase; } ;
struct nn_surveyor {int /*<<< orphan*/  fsm; scalar_t__ timedout; int /*<<< orphan*/  deadline; int /*<<< orphan*/  tosend; int /*<<< orphan*/  timer; int /*<<< orphan*/  surveyid; int /*<<< orphan*/  state; TYPE_1__ xsurveyor; } ;
struct nn_sockbase_vfptr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_SURVEYOR_DEFAULT_DEADLINE ; 
 int /*<<< orphan*/  NN_SURVEYOR_SRC_DEADLINE_TIMER ; 
 int /*<<< orphan*/  NN_SURVEYOR_STATE_IDLE ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_random_generate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_sockbase_getctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_surveyor_handler ; 
 int /*<<< orphan*/  nn_surveyor_shutdown ; 
 int /*<<< orphan*/  nn_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_xsurveyor_init (TYPE_1__*,struct nn_sockbase_vfptr const*,void*) ; 

__attribute__((used)) static void nn_surveyor_init (struct nn_surveyor *self,
    const struct nn_sockbase_vfptr *vfptr, void *hint)
{
    nn_xsurveyor_init (&self->xsurveyor, vfptr, hint);
    nn_fsm_init_root (&self->fsm, nn_surveyor_handler, nn_surveyor_shutdown,
        nn_sockbase_getctx (&self->xsurveyor.sockbase));
    self->state = NN_SURVEYOR_STATE_IDLE;

    /*  Start assigning survey IDs beginning with a random number. This way
        there should be no key clashes even if the executable is re-started. */
    nn_random_generate (&self->surveyid, sizeof (self->surveyid));

    nn_timer_init (&self->timer, NN_SURVEYOR_SRC_DEADLINE_TIMER, &self->fsm);
    nn_msg_init (&self->tosend, 0);
    self->deadline = NN_SURVEYOR_DEFAULT_DEADLINE;
    self->timedout = 0;

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);
}