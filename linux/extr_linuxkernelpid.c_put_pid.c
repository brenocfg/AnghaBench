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
struct pid_namespace {int /*<<< orphan*/  pid_cachep; } ;
struct pid {size_t level; int /*<<< orphan*/  count; TYPE_1__* numbers; } ;
struct TYPE_2__ {struct pid_namespace* ns; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pid*) ; 
 int /*<<< orphan*/  put_pid_ns (struct pid_namespace*) ; 

void put_pid(struct pid *pid)
{
	struct pid_namespace *ns;

	if (!pid)
		return;

	ns = pid->numbers[pid->level].ns;
	if ((atomic_read(&pid->count) == 1) ||
	     atomic_dec_and_test(&pid->count)) {
		kmem_cache_free(ns->pid_cachep, pid);
		put_pid_ns(ns);
	}
}