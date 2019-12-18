#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct name_snapshot {int /*<<< orphan*/  inline_name; TYPE_1__ name; } ;
struct dentry {int /*<<< orphan*/  d_lock; TYPE_1__ d_name; int /*<<< orphan*/  d_iname; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_external (struct dentry*) ; 
 TYPE_3__* external_name (struct dentry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void take_dentry_name_snapshot(struct name_snapshot *name, struct dentry *dentry)
{
	spin_lock(&dentry->d_lock);
	name->name = dentry->d_name;
	if (unlikely(dname_external(dentry))) {
		atomic_inc(&external_name(dentry)->u.count);
	} else {
		memcpy(name->inline_name, dentry->d_iname,
		       dentry->d_name.len + 1);
		name->name.name = name->inline_name;
	}
	spin_unlock(&dentry->d_lock);
}