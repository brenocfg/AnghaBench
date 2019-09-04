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
typedef  scalar_t__ u64 ;
struct kstatfs {scalar_t__ f_blocks; scalar_t__ f_bavail; } ;
struct bsd_acct_struct {int active; scalar_t__ needcheck; TYPE_1__* file; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int ACCT_TIMEOUT ; 
 int HZ ; 
 scalar_t__ RESUME ; 
 scalar_t__ SUSPEND ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ time_is_after_jiffies (scalar_t__) ; 
 scalar_t__ vfs_statfs (int /*<<< orphan*/ *,struct kstatfs*) ; 

__attribute__((used)) static int check_free_space(struct bsd_acct_struct *acct)
{
	struct kstatfs sbuf;

	if (time_is_after_jiffies(acct->needcheck))
		goto out;

	/* May block */
	if (vfs_statfs(&acct->file->f_path, &sbuf))
		goto out;

	if (acct->active) {
		u64 suspend = sbuf.f_blocks * SUSPEND;
		do_div(suspend, 100);
		if (sbuf.f_bavail <= suspend) {
			acct->active = 0;
			pr_info("Process accounting paused\n");
		}
	} else {
		u64 resume = sbuf.f_blocks * RESUME;
		do_div(resume, 100);
		if (sbuf.f_bavail >= resume) {
			acct->active = 1;
			pr_info("Process accounting resumed\n");
		}
	}

	acct->needcheck = jiffies + ACCT_TIMEOUT*HZ;
out:
	return acct->active;
}