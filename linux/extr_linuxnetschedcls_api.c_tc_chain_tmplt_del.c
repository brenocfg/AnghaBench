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
struct tcf_proto_ops {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* tmplt_destroy ) (int /*<<< orphan*/ ) ;} ;
struct tcf_chain {int /*<<< orphan*/  tmplt_priv; struct tcf_proto_ops* tmplt_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc_chain_tmplt_del(struct tcf_chain *chain)
{
	const struct tcf_proto_ops *ops = chain->tmplt_ops;

	/* If template ops are set, no work to do for us. */
	if (!ops)
		return;

	ops->tmplt_destroy(chain->tmplt_priv);
	module_put(ops->owner);
}