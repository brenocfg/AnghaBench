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
struct sysfs_ops {int /*<<< orphan*/  (* store ) (struct kobject*,int /*<<< orphan*/ ,char*,size_t) ;} ;
struct kobject {int dummy; } ;
struct kernfs_open_file {TYPE_2__* kn; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  priv; TYPE_1__* parent; } ;
struct TYPE_3__ {struct kobject* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct kobject*,int /*<<< orphan*/ ,char*,size_t) ; 
 struct sysfs_ops* sysfs_file_ops (TYPE_2__*) ; 

__attribute__((used)) static ssize_t sysfs_kf_write(struct kernfs_open_file *of, char *buf,
			      size_t count, loff_t pos)
{
	const struct sysfs_ops *ops = sysfs_file_ops(of->kn);
	struct kobject *kobj = of->kn->parent->priv;

	if (!count)
		return 0;

	return ops->store(kobj, of->kn->priv, buf, count);
}