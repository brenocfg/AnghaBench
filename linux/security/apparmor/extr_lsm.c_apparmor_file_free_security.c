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
struct aa_file_ctx {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_put_label (int /*<<< orphan*/ ) ; 
 struct aa_file_ctx* file_ctx (struct file*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apparmor_file_free_security(struct file *file)
{
	struct aa_file_ctx *ctx = file_ctx(file);

	if (ctx)
		aa_put_label(rcu_access_pointer(ctx->label));
}