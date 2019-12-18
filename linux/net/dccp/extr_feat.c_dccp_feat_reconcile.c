#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * vec; } ;
struct TYPE_5__ {TYPE_1__ sp; } ;
typedef  TYPE_2__ dccp_feat_val ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CRIT (char*) ; 
 int dccp_feat_prefer (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dccp_feat_preflist_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_feat_reconcile(dccp_feat_val *fv, u8 *arr, u8 len,
			       bool is_server, bool reorder)
{
	int rc;

	if (!fv->sp.vec || !arr) {
		DCCP_CRIT("NULL feature value or array");
		return 0;
	}

	if (is_server)
		rc = dccp_feat_preflist_match(fv->sp.vec, fv->sp.len, arr, len);
	else
		rc = dccp_feat_preflist_match(arr, len, fv->sp.vec, fv->sp.len);

	if (!reorder)
		return rc;
	if (rc < 0)
		return 0;

	/*
	 * Reorder list: used for activating features and in dccp_insert_fn_opt.
	 */
	return dccp_feat_prefer(rc, fv->sp.vec, fv->sp.len);
}