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
struct hci_request {int dummy; } ;
struct hci_dev {scalar_t__ dev_type; } ;
struct amp_mgr {int /*<<< orphan*/  state; } ;
struct a2mp_info_rsp {int /*<<< orphan*/  status; int /*<<< orphan*/  id; } ;
struct a2mp_info_req {int /*<<< orphan*/  id; } ;
struct a2mp_cmd {int /*<<< orphan*/  ident; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  rsp ;

/* Variables and functions */
 int /*<<< orphan*/  A2MP_GETINFO_RSP ; 
 int /*<<< orphan*/  A2MP_STATUS_INVALID_CTRL_ID ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ HCI_AMP ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_AMP_INFO ; 
 int /*<<< orphan*/  READ_LOC_AMP_INFO ; 
 int /*<<< orphan*/  a2mp_send (struct amp_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct a2mp_info_rsp*) ; 
 int /*<<< orphan*/  a2mp_send_getinfo_rsp (struct hci_dev*) ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_local_amp_info_complete ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int a2mp_getinfo_req(struct amp_mgr *mgr, struct sk_buff *skb,
			    struct a2mp_cmd *hdr)
{
	struct a2mp_info_req *req  = (void *) skb->data;
	struct hci_dev *hdev;
	struct hci_request hreq;
	int err = 0;

	if (le16_to_cpu(hdr->len) < sizeof(*req))
		return -EINVAL;

	BT_DBG("id %d", req->id);

	hdev = hci_dev_get(req->id);
	if (!hdev || hdev->dev_type != HCI_AMP) {
		struct a2mp_info_rsp rsp;

		rsp.id = req->id;
		rsp.status = A2MP_STATUS_INVALID_CTRL_ID;

		a2mp_send(mgr, A2MP_GETINFO_RSP, hdr->ident, sizeof(rsp),
			  &rsp);

		goto done;
	}

	set_bit(READ_LOC_AMP_INFO, &mgr->state);
	hci_req_init(&hreq, hdev);
	hci_req_add(&hreq, HCI_OP_READ_LOCAL_AMP_INFO, 0, NULL);
	err = hci_req_run(&hreq, read_local_amp_info_complete);
	if (err < 0)
		a2mp_send_getinfo_rsp(hdev);

done:
	if (hdev)
		hci_dev_put(hdev);

	skb_pull(skb, sizeof(*req));
	return 0;
}