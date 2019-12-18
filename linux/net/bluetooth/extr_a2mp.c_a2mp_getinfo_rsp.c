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
struct sk_buff {scalar_t__ data; } ;
struct amp_mgr {int dummy; } ;
struct amp_ctrl {int dummy; } ;
struct a2mp_info_rsp {int /*<<< orphan*/  id; scalar_t__ status; } ;
struct a2mp_cmd {int /*<<< orphan*/  len; } ;
struct a2mp_amp_assoc_req {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  A2MP_GETAMPASSOC_REQ ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __next_ident (struct amp_mgr*) ; 
 int /*<<< orphan*/  a2mp_send (struct amp_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct a2mp_amp_assoc_req*) ; 
 struct amp_ctrl* amp_ctrl_add (struct amp_mgr*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int a2mp_getinfo_rsp(struct amp_mgr *mgr, struct sk_buff *skb,
			    struct a2mp_cmd *hdr)
{
	struct a2mp_info_rsp *rsp = (struct a2mp_info_rsp *) skb->data;
	struct a2mp_amp_assoc_req req;
	struct amp_ctrl *ctrl;

	if (le16_to_cpu(hdr->len) < sizeof(*rsp))
		return -EINVAL;

	BT_DBG("id %d status 0x%2.2x", rsp->id, rsp->status);

	if (rsp->status)
		return -EINVAL;

	ctrl = amp_ctrl_add(mgr, rsp->id);
	if (!ctrl)
		return -ENOMEM;

	req.id = rsp->id;
	a2mp_send(mgr, A2MP_GETAMPASSOC_REQ, __next_ident(mgr), sizeof(req),
		  &req);

	skb_pull(skb, sizeof(*rsp));
	return 0;
}