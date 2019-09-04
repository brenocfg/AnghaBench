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
struct name_snapshot {int /*<<< orphan*/  inline_name; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct external_name {int /*<<< orphan*/  name; TYPE_1__ u; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_2__ d_name; int /*<<< orphan*/  d_iname; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_external (struct dentry*) ; 
 struct external_name* external_name (struct dentry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void take_dentry_name_snapshot(struct name_snapshot *name, struct dentry *dentry)
{
	spin_lock(&dentry->d_lock);
	if (unlikely(dname_external(dentry))) {
		struct external_name *p = external_name(dentry);
		atomic_inc(&p->u.count);
		spin_unlock(&dentry->d_lock);
		name->name = p->name;
	} else {
		memcpy(name->inline_name, dentry->d_iname,
		       dentry->d_name.len + 1);
		spin_unlock(&dentry->d_lock);
		name->name = name->inline_name;
	}
}