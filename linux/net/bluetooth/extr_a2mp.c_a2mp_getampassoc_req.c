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
struct hci_dev {scalar_t__ amp_type; } ;
struct amp_mgr {int dummy; } ;
struct a2mp_cmd {int /*<<< orphan*/  ident; int /*<<< orphan*/  len; } ;
struct a2mp_amp_assoc_rsp {int /*<<< orphan*/  status; int /*<<< orphan*/  id; } ;
struct a2mp_amp_assoc_req {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  rsp ;

/* Variables and functions */
 int /*<<< orphan*/  A2MP_GETAMPASSOC_RSP ; 
 int /*<<< orphan*/  A2MP_STATUS_COLLISION_OCCURED ; 
 int /*<<< orphan*/  A2MP_STATUS_INVALID_CTRL_ID ; 
 scalar_t__ AMP_TYPE_BREDR ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  READ_LOC_AMP_ASSOC ; 
 int /*<<< orphan*/  a2mp_send (struct amp_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct a2mp_amp_assoc_rsp*) ; 
 struct amp_mgr* amp_mgr_lookup_by_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amp_mgr_put (struct amp_mgr*) ; 
 int /*<<< orphan*/  amp_read_loc_assoc (struct hci_dev*,struct amp_mgr*) ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int a2mp_getampassoc_req(struct amp_mgr *mgr, struct sk_buff *skb,
				struct a2mp_cmd *hdr)
{
	struct a2mp_amp_assoc_req *req = (void *) skb->data;
	struct hci_dev *hdev;
	struct amp_mgr *tmp;

	if (le16_to_cpu(hdr->len) < sizeof(*req))
		return -EINVAL;

	BT_DBG("id %d", req->id);

	/* Make sure that other request is not processed */
	tmp = amp_mgr_lookup_by_state(READ_LOC_AMP_ASSOC);

	hdev = hci_dev_get(req->id);
	if (!hdev || hdev->amp_type == AMP_TYPE_BREDR || tmp) {
		struct a2mp_amp_assoc_rsp rsp;
		rsp.id = req->id;

		if (tmp) {
			rsp.status = A2MP_STATUS_COLLISION_OCCURED;
			amp_mgr_put(tmp);
		} else {
			rsp.status = A2MP_STATUS_INVALID_CTRL_ID;
		}

		a2mp_send(mgr, A2MP_GETAMPASSOC_RSP, hdr->ident, sizeof(rsp),
			  &rsp);

		goto done;
	}

	amp_read_loc_assoc(hdev, mgr);

done:
	if (hdev)
		hci_dev_put(hdev);

	skb_pull(skb, sizeof(*req));
	return 0;
}