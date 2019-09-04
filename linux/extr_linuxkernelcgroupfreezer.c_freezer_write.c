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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_FROZEN ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  css_freezer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freezer_change_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freezer_state_strs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strstrip (char*) ; 

__attribute__((used)) static ssize_t freezer_write(struct kernfs_open_file *of,
			     char *buf, size_t nbytes, loff_t off)
{
	bool freeze;

	buf = strstrip(buf);

	if (strcmp(buf, freezer_state_strs(0)) == 0)
		freeze = false;
	else if (strcmp(buf, freezer_state_strs(CGROUP_FROZEN)) == 0)
		freeze = true;
	else
		return -EINVAL;

	freezer_change_state(css_freezer(of_css(of)), freeze);
	return nbytes;
}