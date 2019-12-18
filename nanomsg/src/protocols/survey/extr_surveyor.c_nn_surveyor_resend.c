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
struct nn_surveyor {TYPE_1__ xsurveyor; int /*<<< orphan*/  tosend; } ;
struct nn_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  nn_msg_cp (struct nn_msg*,int /*<<< orphan*/ *) ; 
 int nn_xsurveyor_send (int /*<<< orphan*/ *,struct nn_msg*) ; 

__attribute__((used)) static void nn_surveyor_resend (struct nn_surveyor *self)
{
    int rc;
    struct nn_msg msg;

    nn_msg_cp (&msg, &self->tosend);
    rc = nn_xsurveyor_send (&self->xsurveyor.sockbase, &msg);
    errnum_assert (rc == 0, -rc);
}