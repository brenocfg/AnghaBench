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
struct aa_label {int dummy; } ;
struct aa_file_ctx {int /*<<< orphan*/  label; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  aa_get_label (struct aa_label*) ; 
 struct aa_file_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct aa_file_ctx *aa_alloc_file_ctx(struct aa_label *label,
						    gfp_t gfp)
{
	struct aa_file_ctx *ctx;

	ctx = kzalloc(sizeof(struct aa_file_ctx), gfp);
	if (ctx) {
		spin_lock_init(&ctx->lock);
		rcu_assign_pointer(ctx->label, aa_get_label(label));
	}
	return ctx;
}