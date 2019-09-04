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
struct aa_file_ctx {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_put_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct aa_file_ctx*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aa_free_file_ctx(struct aa_file_ctx *ctx)
{
	if (ctx) {
		aa_put_label(rcu_access_pointer(ctx->label));
		kzfree(ctx);
	}
}