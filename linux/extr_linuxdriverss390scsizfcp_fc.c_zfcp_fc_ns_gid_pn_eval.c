#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_ct_els {TYPE_4__* port; scalar_t__ status; } ;
struct TYPE_10__ {int /*<<< orphan*/  fp_fid; } ;
struct TYPE_8__ {scalar_t__ ct_cmd; } ;
struct zfcp_fc_gid_pn_rsp {TYPE_5__ gid_pn; TYPE_3__ ct_hdr; } ;
struct TYPE_6__ {struct zfcp_fc_gid_pn_rsp rsp; } ;
struct TYPE_7__ {TYPE_1__ gid_pn; } ;
struct zfcp_fc_req {TYPE_2__ u; struct zfcp_fsf_ct_els ct_els; } ;
struct TYPE_9__ {int /*<<< orphan*/  d_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_FS_ACC ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_fc_ns_gid_pn_eval(struct zfcp_fc_req *fc_req)
{
	struct zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	struct zfcp_fc_gid_pn_rsp *gid_pn_rsp = &fc_req->u.gid_pn.rsp;

	if (ct_els->status)
		return;
	if (gid_pn_rsp->ct_hdr.ct_cmd != cpu_to_be16(FC_FS_ACC))
		return;

	/* looks like a valid d_id */
	ct_els->port->d_id = ntoh24(gid_pn_rsp->gid_pn.fp_fid);
}