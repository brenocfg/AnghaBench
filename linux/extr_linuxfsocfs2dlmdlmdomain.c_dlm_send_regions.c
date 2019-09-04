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
struct dlm_query_region {int qr_node; int qr_numregions; char* qr_regions; int /*<<< orphan*/  qr_namelen; int /*<<< orphan*/  qr_domain; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MOD_KEY ; 
 int /*<<< orphan*/  DLM_QUERY_REGION ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  O2HB_MAX_REGION_NAME_LEN ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  O2NM_MAX_REGIONS ; 
 int find_next_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  kfree (struct dlm_query_region*) ; 
 struct dlm_query_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2hb_get_all_regions (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ o2hb_global_heartbeat_active () ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_query_region*,int,int,int*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_send_regions(struct dlm_ctxt *dlm, unsigned long *node_map)
{
	struct dlm_query_region *qr = NULL;
	int status, ret = 0, i;
	char *p;

	if (find_next_bit(node_map, O2NM_MAX_NODES, 0) >= O2NM_MAX_NODES)
		goto bail;

	qr = kzalloc(sizeof(struct dlm_query_region), GFP_KERNEL);
	if (!qr) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto bail;
	}

	qr->qr_node = dlm->node_num;
	qr->qr_namelen = strlen(dlm->name);
	memcpy(qr->qr_domain, dlm->name, qr->qr_namelen);
	/* if local hb, the numregions will be zero */
	if (o2hb_global_heartbeat_active())
		qr->qr_numregions = o2hb_get_all_regions(qr->qr_regions,
							 O2NM_MAX_REGIONS);

	p = qr->qr_regions;
	for (i = 0; i < qr->qr_numregions; ++i, p += O2HB_MAX_REGION_NAME_LEN)
		mlog(0, "Region %.*s\n", O2HB_MAX_REGION_NAME_LEN, p);

	i = -1;
	while ((i = find_next_bit(node_map, O2NM_MAX_NODES,
				  i + 1)) < O2NM_MAX_NODES) {
		if (i == dlm->node_num)
			continue;

		mlog(0, "Sending regions to node %d\n", i);

		ret = o2net_send_message(DLM_QUERY_REGION, DLM_MOD_KEY, qr,
					 sizeof(struct dlm_query_region),
					 i, &status);
		if (ret >= 0)
			ret = status;
		if (ret) {
			mlog(ML_ERROR, "Region mismatch %d, node %d\n",
			     ret, i);
			break;
		}
	}

bail:
	kfree(qr);
	return ret;
}