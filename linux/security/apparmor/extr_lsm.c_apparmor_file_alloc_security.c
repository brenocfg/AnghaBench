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
struct file {int dummy; } ;
struct aa_label {int dummy; } ;
struct aa_file_ctx {int /*<<< orphan*/  label; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_get_label (struct aa_label*) ; 
 struct aa_label* begin_current_label_crit_section () ; 
 int /*<<< orphan*/  end_current_label_crit_section (struct aa_label*) ; 
 struct aa_file_ctx* file_ctx (struct file*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apparmor_file_alloc_security(struct file *file)
{
	struct aa_file_ctx *ctx = file_ctx(file);
	struct aa_label *label = begin_current_label_crit_section();

	spin_lock_init(&ctx->lock);
	rcu_assign_pointer(ctx->label, aa_get_label(label));
	end_current_label_crit_section(label);
	return 0;
}