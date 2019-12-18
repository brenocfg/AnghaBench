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
typedef  int /*<<< orphan*/  u8 ;
struct list_head {int dummy; } ;
struct ccid_dependency {scalar_t__ dependent_feat; int /*<<< orphan*/  val; int /*<<< orphan*/  is_mandatory; int /*<<< orphan*/  is_local; } ;

/* Variables and functions */
 scalar_t__ DCCPF_RESERVED ; 
 scalar_t__ FEAT_SP ; 
 int __feat_register_nn (struct list_head*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __feat_register_sp (struct list_head*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct ccid_dependency* dccp_feat_ccid_deps (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dccp_feat_type (scalar_t__) ; 

__attribute__((used)) static int dccp_feat_propagate_ccid(struct list_head *fn, u8 id, bool is_local)
{
	const struct ccid_dependency *table = dccp_feat_ccid_deps(id, is_local);
	int i, rc = (table == NULL);

	for (i = 0; rc == 0 && table[i].dependent_feat != DCCPF_RESERVED; i++)
		if (dccp_feat_type(table[i].dependent_feat) == FEAT_SP)
			rc = __feat_register_sp(fn, table[i].dependent_feat,
						    table[i].is_local,
						    table[i].is_mandatory,
						    &table[i].val, 1);
		else
			rc = __feat_register_nn(fn, table[i].dependent_feat,
						    table[i].is_mandatory,
						    table[i].val);
	return rc;
}