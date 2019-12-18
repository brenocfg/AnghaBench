#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ctl_table; struct ctl_dir* parent; } ;
struct ctl_dir {TYPE_2__ header; } ;
struct ctl_table_set {struct ctl_dir dir; } ;
struct TYPE_3__ {char* procname; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ctl_dir*) ; 
 struct ctl_dir* find_subdir (struct ctl_dir*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct ctl_dir *xlate_dir(struct ctl_table_set *set, struct ctl_dir *dir)
{
	struct ctl_dir *parent;
	const char *procname;
	if (!dir->header.parent)
		return &set->dir;
	parent = xlate_dir(set, dir->header.parent);
	if (IS_ERR(parent))
		return parent;
	procname = dir->header.ctl_table[0].procname;
	return find_subdir(parent, procname, strlen(procname));
}