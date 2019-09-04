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
struct file {int /*<<< orphan*/  f_security; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  aa_alloc_file_ctx (struct aa_label*,int /*<<< orphan*/ ) ; 
 struct aa_label* begin_current_label_crit_section () ; 
 int /*<<< orphan*/  end_current_label_crit_section (struct aa_label*) ; 
 int /*<<< orphan*/  file_ctx (struct file*) ; 

__attribute__((used)) static int apparmor_file_alloc_security(struct file *file)
{
	int error = 0;

	/* freed by apparmor_file_free_security */
	struct aa_label *label = begin_current_label_crit_section();
	file->f_security = aa_alloc_file_ctx(label, GFP_KERNEL);
	if (!file_ctx(file))
		error = -ENOMEM;
	end_current_label_crit_section(label);

	return error;
}