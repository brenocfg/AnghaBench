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
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  kernfs_path (struct kernfs_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,char const*) ; 

void sysfs_warn_dup(struct kernfs_node *parent, const char *name)
{
	char *buf;

	buf = kzalloc(PATH_MAX, GFP_KERNEL);
	if (buf)
		kernfs_path(parent, buf, PATH_MAX);

	pr_warn("cannot create duplicate filename '%s/%s'\n", buf, name);
	dump_stack();

	kfree(buf);
}