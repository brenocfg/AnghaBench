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
struct tcf_proto_ops {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* tmplt_destroy ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void tc_chain_tmplt_del(const struct tcf_proto_ops *tmplt_ops,
			       void *tmplt_priv)
{
	/* If template ops are set, no work to do for us. */
	if (!tmplt_ops)
		return;

	tmplt_ops->tmplt_destroy(tmplt_priv);
	module_put(tmplt_ops->owner);
}