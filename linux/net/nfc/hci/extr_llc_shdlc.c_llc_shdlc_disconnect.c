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
struct llc_shdlc {int /*<<< orphan*/  sm_work; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHDLC_DISCONNECTED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void llc_shdlc_disconnect(struct llc_shdlc *shdlc)
{
	pr_debug("\n");

	mutex_lock(&shdlc->state_mutex);

	shdlc->state = SHDLC_DISCONNECTED;

	mutex_unlock(&shdlc->state_mutex);

	schedule_work(&shdlc->sm_work);
}