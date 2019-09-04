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
struct vscsiif_back_ring {int dummy; } ;
struct TYPE_2__ {int map_tag; int map_cpu; } ;
struct vscsibk_pend {int /*<<< orphan*/ * grant_handles; TYPE_1__ se_cmd; } ;
struct v2p_entry {struct scsiback_tpg* tpg; } ;
struct se_session {scalar_t__ sess_cmd_map; int /*<<< orphan*/  sess_tag_pool; } ;
struct scsiback_tpg {struct scsiback_nexus* tpg_nexus; } ;
struct scsiback_nexus {struct se_session* tvn_se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vscsibk_pend* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSIBACK_INVALID_HANDLE ; 
 int VSCSI_MAX_GRANTS ; 
 int /*<<< orphan*/  memset (struct vscsibk_pend*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sbitmap_queue_get (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static struct vscsibk_pend *scsiback_get_pend_req(struct vscsiif_back_ring *ring,
				struct v2p_entry *v2p)
{
	struct scsiback_tpg *tpg = v2p->tpg;
	struct scsiback_nexus *nexus = tpg->tpg_nexus;
	struct se_session *se_sess = nexus->tvn_se_sess;
	struct vscsibk_pend *req;
	int tag, cpu, i;

	tag = sbitmap_queue_get(&se_sess->sess_tag_pool, &cpu);
	if (tag < 0) {
		pr_err("Unable to obtain tag for vscsiif_request\n");
		return ERR_PTR(-ENOMEM);
	}

	req = &((struct vscsibk_pend *)se_sess->sess_cmd_map)[tag];
	memset(req, 0, sizeof(*req));
	req->se_cmd.map_tag = tag;
	req->se_cmd.map_cpu = cpu;

	for (i = 0; i < VSCSI_MAX_GRANTS; i++)
		req->grant_handles[i] = SCSIBACK_INVALID_HANDLE;

	return req;
}