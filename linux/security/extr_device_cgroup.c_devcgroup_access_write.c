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
struct kernfs_open_file {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_to_devcgroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devcgroup_mutex ; 
 int devcgroup_update_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* of_cft (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  of_css (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  strstrip (char*) ; 

__attribute__((used)) static ssize_t devcgroup_access_write(struct kernfs_open_file *of,
				      char *buf, size_t nbytes, loff_t off)
{
	int retval;

	mutex_lock(&devcgroup_mutex);
	retval = devcgroup_update_access(css_to_devcgroup(of_css(of)),
					 of_cft(of)->private, strstrip(buf));
	mutex_unlock(&devcgroup_mutex);
	return retval ?: nbytes;
}