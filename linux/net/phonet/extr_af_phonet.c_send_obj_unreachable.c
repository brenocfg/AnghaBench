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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct phonetmsg {scalar_t__ pn_status; int /*<<< orphan*/  pn_msg_id; int /*<<< orphan*/  pn_orig_msg_id; void* pn_submsg_id; scalar_t__ pn_e_status; int /*<<< orphan*/  pn_e_orig_msg_id; void* pn_e_submsg_id; int /*<<< orphan*/  pn_e_res_id; int /*<<< orphan*/  pn_trans_id; } ;
struct phonethdr {scalar_t__ pn_res; int /*<<< orphan*/  pn_robj; int /*<<< orphan*/  pn_rdev; int /*<<< orphan*/  pn_sobj; int /*<<< orphan*/  pn_sdev; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int /*<<< orphan*/  PN_COMMON_MESSAGE ; 
 void* PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP ; 
 scalar_t__ PN_PREFIX ; 
 int /*<<< orphan*/  memset (struct phonetmsg*,int /*<<< orphan*/ ,int) ; 
 struct phonethdr* pn_hdr (struct sk_buff*) ; 
 struct phonetmsg* pn_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  pn_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pn_raw_send (struct phonetmsg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int send_obj_unreachable(struct sk_buff *rskb)
{
	const struct phonethdr *oph = pn_hdr(rskb);
	const struct phonetmsg *opm = pn_msg(rskb);
	struct phonetmsg resp;

	memset(&resp, 0, sizeof(resp));
	resp.pn_trans_id = opm->pn_trans_id;
	resp.pn_msg_id = PN_COMMON_MESSAGE;
	if (oph->pn_res == PN_PREFIX) {
		resp.pn_e_res_id = opm->pn_e_res_id;
		resp.pn_e_submsg_id = PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP;
		resp.pn_e_orig_msg_id = opm->pn_msg_id;
		resp.pn_e_status = 0;
	} else {
		resp.pn_submsg_id = PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP;
		resp.pn_orig_msg_id = opm->pn_msg_id;
		resp.pn_status = 0;
	}
	return pn_raw_send(&resp, sizeof(resp), rskb->dev,
				pn_object(oph->pn_sdev, oph->pn_sobj),
				pn_object(oph->pn_rdev, oph->pn_robj),
				oph->pn_res);
}