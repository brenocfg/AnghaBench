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
struct ce_unbind {int res; int /*<<< orphan*/  ce; } ;

/* Variables and functions */
 int EAGAIN ; 
 int __clockevents_try_unbind (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clockevents_lock ; 
 int clockevents_replace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void __clockevents_unbind(void *arg)
{
	struct ce_unbind *cu = arg;
	int res;

	raw_spin_lock(&clockevents_lock);
	res = __clockevents_try_unbind(cu->ce, smp_processor_id());
	if (res == -EAGAIN)
		res = clockevents_replace(cu->ce);
	cu->res = res;
	raw_spin_unlock(&clockevents_lock);
}