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
struct path {int dummy; } ;
struct dentry {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int aa_path_link (struct aa_label*,struct dentry*,struct path const*,struct dentry*) ; 
 struct aa_label* begin_current_label_crit_section () ; 
 int /*<<< orphan*/  end_current_label_crit_section (struct aa_label*) ; 
 int /*<<< orphan*/  path_mediated_fs (struct dentry*) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

__attribute__((used)) static int apparmor_path_link(struct dentry *old_dentry, const struct path *new_dir,
			      struct dentry *new_dentry)
{
	struct aa_label *label;
	int error = 0;

	if (!path_mediated_fs(old_dentry))
		return 0;

	label = begin_current_label_crit_section();
	if (!unconfined(label))
		error = aa_path_link(label, old_dentry, new_dir, new_dentry);
	end_current_label_crit_section(label);

	return error;
}