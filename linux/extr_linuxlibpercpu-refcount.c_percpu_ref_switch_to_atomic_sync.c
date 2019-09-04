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
struct percpu_ref {int /*<<< orphan*/  confirm_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_ref_switch_to_atomic (struct percpu_ref*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_switch_waitq ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void percpu_ref_switch_to_atomic_sync(struct percpu_ref *ref)
{
	percpu_ref_switch_to_atomic(ref, NULL);
	wait_event(percpu_ref_switch_waitq, !ref->confirm_switch);
}