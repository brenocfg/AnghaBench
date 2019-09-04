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
struct inode {struct aa_proxy* i_private; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
struct aa_proxy {int /*<<< orphan*/  label; } ;
struct aa_profile {TYPE_1__* rawdata; } ;
struct aa_label {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (char*) ; 
 struct aa_label* aa_get_label_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 char* gen_symlink_name (int,int /*<<< orphan*/ ,char const*) ; 
 struct aa_profile* labels_profile (struct aa_label*) ; 
 int profile_depth (struct aa_profile*) ; 
 int /*<<< orphan*/  rawdata_link_cb ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *rawdata_get_link_base(struct dentry *dentry,
					 struct inode *inode,
					 struct delayed_call *done,
					 const char *name)
{
	struct aa_proxy *proxy = inode->i_private;
	struct aa_label *label;
	struct aa_profile *profile;
	char *target;
	int depth;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	label = aa_get_label_rcu(&proxy->label);
	profile = labels_profile(label);
	depth = profile_depth(profile);
	target = gen_symlink_name(depth, profile->rawdata->name, name);
	aa_put_label(label);

	if (IS_ERR(target))
		return target;

	set_delayed_call(done, rawdata_link_cb, target);

	return target;
}