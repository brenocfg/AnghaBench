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
struct gsm_mux {int /*<<< orphan*/  event; } ;
struct gsm_control {int done; int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gsm_control*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gsm_control_wait(struct gsm_mux *gsm, struct gsm_control *control)
{
	int err;
	wait_event(gsm->event, control->done == 1);
	err = control->error;
	kfree(control);
	return err;
}