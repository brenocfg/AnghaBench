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
struct signal_struct {scalar_t__ oom_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct signal_struct*) ; 
 int /*<<< orphan*/  mmdrop_async (scalar_t__) ; 
 int /*<<< orphan*/  sched_autogroup_exit (struct signal_struct*) ; 
 int /*<<< orphan*/  signal_cachep ; 
 int /*<<< orphan*/  taskstats_tgid_free (struct signal_struct*) ; 

__attribute__((used)) static inline void free_signal_struct(struct signal_struct *sig)
{
	taskstats_tgid_free(sig);
	sched_autogroup_exit(sig);
	/*
	 * __mmdrop is not safe to call from softirq context on x86 due to
	 * pgd_dtor so postpone it to the async context
	 */
	if (sig->oom_mm)
		mmdrop_async(sig->oom_mm);
	kmem_cache_free(signal_cachep, sig);
}