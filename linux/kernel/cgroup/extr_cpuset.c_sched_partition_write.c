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
struct kernfs_open_file {int dummy; } ;
struct cpuset {int /*<<< orphan*/  css; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int ENODEV ; 
 int PRS_DISABLED ; 
 int PRS_ENABLED ; 
 int /*<<< orphan*/  cpuset_rwsem ; 
 struct cpuset* css_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  is_cpuset_online (struct cpuset*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strstrip (char*) ; 
 int update_prstate (struct cpuset*,int) ; 

__attribute__((used)) static ssize_t sched_partition_write(struct kernfs_open_file *of, char *buf,
				     size_t nbytes, loff_t off)
{
	struct cpuset *cs = css_cs(of_css(of));
	int val;
	int retval = -ENODEV;

	buf = strstrip(buf);

	/*
	 * Convert "root" to ENABLED, and convert "member" to DISABLED.
	 */
	if (!strcmp(buf, "root"))
		val = PRS_ENABLED;
	else if (!strcmp(buf, "member"))
		val = PRS_DISABLED;
	else
		return -EINVAL;

	css_get(&cs->css);
	get_online_cpus();
	percpu_down_write(&cpuset_rwsem);
	if (!is_cpuset_online(cs))
		goto out_unlock;

	retval = update_prstate(cs, val);
out_unlock:
	percpu_up_write(&cpuset_rwsem);
	put_online_cpus();
	css_put(&cs->css);
	return retval ?: nbytes;
}