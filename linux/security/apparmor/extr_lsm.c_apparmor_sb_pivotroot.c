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
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_label* aa_get_current_label () ; 
 int aa_pivotroot (struct aa_label*,struct path const*,struct path const*) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

__attribute__((used)) static int apparmor_sb_pivotroot(const struct path *old_path,
				 const struct path *new_path)
{
	struct aa_label *label;
	int error = 0;

	label = aa_get_current_label();
	if (!unconfined(label))
		error = aa_pivotroot(label, old_path, new_path);
	aa_put_label(label);

	return error;
}