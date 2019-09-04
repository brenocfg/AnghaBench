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
struct file {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {long max_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  ENFILE ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct file*) ; 
 struct file* __alloc_file (int,struct cred const*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__ files_stat ; 
 int /*<<< orphan*/  get_max_files () ; 
 long get_nr_files () ; 
 int /*<<< orphan*/  nr_files ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ percpu_counter_sum_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

struct file *alloc_empty_file(int flags, const struct cred *cred)
{
	static long old_max;
	struct file *f;

	/*
	 * Privileged users can go above max_files
	 */
	if (get_nr_files() >= files_stat.max_files && !capable(CAP_SYS_ADMIN)) {
		/*
		 * percpu_counters are inaccurate.  Do an expensive check before
		 * we go and fail.
		 */
		if (percpu_counter_sum_positive(&nr_files) >= files_stat.max_files)
			goto over;
	}

	f = __alloc_file(flags, cred);
	if (!IS_ERR(f))
		percpu_counter_inc(&nr_files);

	return f;

over:
	/* Ran out of filps - report that */
	if (get_nr_files() > old_max) {
		pr_info("VFS: file-max limit %lu reached\n", get_max_files());
		old_max = get_nr_files();
	}
	return ERR_PTR(-ENFILE);
}