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
struct dlm_query_region {char* qr_regions; int qr_numregions; int /*<<< orphan*/  qr_node; int /*<<< orphan*/  qr_domain; } ;
struct dlm_ctxt {int /*<<< orphan*/  node_num; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int O2HB_MAX_REGION_NAME_LEN ; 
 int /*<<< orphan*/  O2NM_MAX_REGIONS ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int o2hb_get_all_regions (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ o2hb_global_heartbeat_active () ; 

__attribute__((used)) static int dlm_match_regions(struct dlm_ctxt *dlm,
			     struct dlm_query_region *qr,
			     char *local, int locallen)
{
	char *remote = qr->qr_regions;
	char *l, *r;
	int localnr, i, j, foundit;
	int status = 0;

	if (!o2hb_global_heartbeat_active()) {
		if (qr->qr_numregions) {
			mlog(ML_ERROR, "Domain %s: Joining node %d has global "
			     "heartbeat enabled but local node %d does not\n",
			     qr->qr_domain, qr->qr_node, dlm->node_num);
			status = -EINVAL;
		}
		goto bail;
	}

	if (o2hb_global_heartbeat_active() && !qr->qr_numregions) {
		mlog(ML_ERROR, "Domain %s: Local node %d has global "
		     "heartbeat enabled but joining node %d does not\n",
		     qr->qr_domain, dlm->node_num, qr->qr_node);
		status = -EINVAL;
		goto bail;
	}

	r = remote;
	for (i = 0; i < qr->qr_numregions; ++i) {
		mlog(0, "Region %.*s\n", O2HB_MAX_REGION_NAME_LEN, r);
		r += O2HB_MAX_REGION_NAME_LEN;
	}

	localnr = min(O2NM_MAX_REGIONS, locallen/O2HB_MAX_REGION_NAME_LEN);
	localnr = o2hb_get_all_regions(local, (u8)localnr);

	/* compare local regions with remote */
	l = local;
	for (i = 0; i < localnr; ++i) {
		foundit = 0;
		r = remote;
		for (j = 0; j <= qr->qr_numregions; ++j) {
			if (!memcmp(l, r, O2HB_MAX_REGION_NAME_LEN)) {
				foundit = 1;
				break;
			}
			r += O2HB_MAX_REGION_NAME_LEN;
		}
		if (!foundit) {
			status = -EINVAL;
			mlog(ML_ERROR, "Domain %s: Region '%.*s' registered "
			     "in local node %d but not in joining node %d\n",
			     qr->qr_domain, O2HB_MAX_REGION_NAME_LEN, l,
			     dlm->node_num, qr->qr_node);
			goto bail;
		}
		l += O2HB_MAX_REGION_NAME_LEN;
	}

	/* compare remote with local regions */
	r = remote;
	for (i = 0; i < qr->qr_numregions; ++i) {
		foundit = 0;
		l = local;
		for (j = 0; j < localnr; ++j) {
			if (!memcmp(r, l, O2HB_MAX_REGION_NAME_LEN)) {
				foundit = 1;
				break;
			}
			l += O2HB_MAX_REGION_NAME_LEN;
		}
		if (!foundit) {
			status = -EINVAL;
			mlog(ML_ERROR, "Domain %s: Region '%.*s' registered "
			     "in joining node %d but not in local node %d\n",
			     qr->qr_domain, O2HB_MAX_REGION_NAME_LEN, r,
			     qr->qr_node, dlm->node_num);
			goto bail;
		}
		r += O2HB_MAX_REGION_NAME_LEN;
	}

bail:
	return status;
}