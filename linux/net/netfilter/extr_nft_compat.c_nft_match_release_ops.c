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
struct xt_match {int /*<<< orphan*/  me; } ;
struct nft_expr_ops {struct xt_match* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nft_expr_ops const*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_match_release_ops(const struct nft_expr_ops *ops)
{
	struct xt_match *match = ops->data;

	module_put(match->me);
	kfree(ops);
}