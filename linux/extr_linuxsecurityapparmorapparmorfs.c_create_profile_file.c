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
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;
struct aa_proxy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proxy; } ;
struct aa_profile {TYPE_1__ label; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int S_IFREG ; 
 struct aa_proxy* aa_get_proxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_proxy (struct aa_proxy*) ; 
 struct dentry* aafs_create_file (char const*,int,struct dentry*,struct aa_proxy*,struct file_operations const*) ; 

__attribute__((used)) static struct dentry *create_profile_file(struct dentry *dir, const char *name,
					  struct aa_profile *profile,
					  const struct file_operations *fops)
{
	struct aa_proxy *proxy = aa_get_proxy(profile->label.proxy);
	struct dentry *dent;

	dent = aafs_create_file(name, S_IFREG | 0444, dir, proxy, fops);
	if (IS_ERR(dent))
		aa_put_proxy(proxy);

	return dent;
}