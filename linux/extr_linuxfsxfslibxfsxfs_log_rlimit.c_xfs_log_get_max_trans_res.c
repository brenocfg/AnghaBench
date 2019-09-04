#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_trans_res {int tr_logcount; int tr_logres; } ;
struct xfs_mount {int dummy; } ;
struct TYPE_2__ {struct xfs_trans_res tr_attrsetm; } ;

/* Variables and functions */
 TYPE_1__* M_RES (struct xfs_mount*) ; 
 int xfs_log_calc_max_attrsetm_res (struct xfs_mount*) ; 

void
xfs_log_get_max_trans_res(
	struct xfs_mount	*mp,
	struct xfs_trans_res	*max_resp)
{
	struct xfs_trans_res	*resp;
	struct xfs_trans_res	*end_resp;
	int			log_space = 0;
	int			attr_space;

	attr_space = xfs_log_calc_max_attrsetm_res(mp);

	resp = (struct xfs_trans_res *)M_RES(mp);
	end_resp = (struct xfs_trans_res *)(M_RES(mp) + 1);
	for (; resp < end_resp; resp++) {
		int		tmp = resp->tr_logcount > 1 ?
				      resp->tr_logres * resp->tr_logcount :
				      resp->tr_logres;
		if (log_space < tmp) {
			log_space = tmp;
			*max_resp = *resp;		/* struct copy */
		}
	}

	if (attr_space > log_space) {
		*max_resp = M_RES(mp)->tr_attrsetm;	/* struct copy */
		max_resp->tr_logres = attr_space;
	}
}