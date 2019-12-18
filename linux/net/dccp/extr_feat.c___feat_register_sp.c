#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct list_head {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  vec; } ;
struct TYPE_6__ {TYPE_1__ sp; } ;
typedef  TYPE_2__ dccp_feat_val ;

/* Variables and functions */
 scalar_t__ DCCPF_CCID ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ FEAT_SP ; 
 int /*<<< orphan*/  ccid_support_check (scalar_t__ const*,scalar_t__) ; 
 scalar_t__ dccp_feat_clone_sp_val (TYPE_2__*,scalar_t__ const*,scalar_t__) ; 
 scalar_t__ dccp_feat_push_change (struct list_head*,scalar_t__,scalar_t__,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  dccp_feat_sp_list_ok (scalar_t__,scalar_t__ const*,scalar_t__) ; 
 scalar_t__ dccp_feat_type (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __feat_register_sp(struct list_head *fn, u8 feat, u8 is_local,
			      u8 mandatory, u8 const *sp_val, u8 sp_len)
{
	dccp_feat_val fval;

	if (dccp_feat_type(feat) != FEAT_SP ||
	    !dccp_feat_sp_list_ok(feat, sp_val, sp_len))
		return -EINVAL;

	/* Avoid negotiating alien CCIDs by only advertising supported ones */
	if (feat == DCCPF_CCID && !ccid_support_check(sp_val, sp_len))
		return -EOPNOTSUPP;

	if (dccp_feat_clone_sp_val(&fval, sp_val, sp_len))
		return -ENOMEM;

	if (dccp_feat_push_change(fn, feat, is_local, mandatory, &fval)) {
		kfree(fval.sp.vec);
		return -ENOMEM;
	}

	return 0;
}