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
struct xt_target {int /*<<< orphan*/  me; } ;
struct nft_expr_ops {struct xt_target* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nft_expr_ops const*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_target_release_ops(const struct nft_expr_ops *ops)
{
	struct xt_target *target = ops->data;

	module_put(target->me);
	kfree(ops);
}