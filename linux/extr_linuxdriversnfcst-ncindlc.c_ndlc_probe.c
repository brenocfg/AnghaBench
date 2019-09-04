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
struct st_nci_se_status {int dummy; } ;
struct nfc_phy_ops {int dummy; } ;
struct llt_ndlc {int /*<<< orphan*/  sm_work; int /*<<< orphan*/  ack_pending_q; int /*<<< orphan*/  send_q; int /*<<< orphan*/  rcv_q; int /*<<< orphan*/  t2_timer; int /*<<< orphan*/  t1_timer; scalar_t__ powered; struct device* dev; void* phy_id; struct nfc_phy_ops* ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct llt_ndlc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llt_ndlc_sm_work ; 
 int /*<<< orphan*/  ndlc_t1_timeout ; 
 int /*<<< orphan*/  ndlc_t2_timeout ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int st_nci_probe (struct llt_ndlc*,int,int,struct st_nci_se_status*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ndlc_probe(void *phy_id, struct nfc_phy_ops *phy_ops, struct device *dev,
	       int phy_headroom, int phy_tailroom, struct llt_ndlc **ndlc_id,
	       struct st_nci_se_status *se_status)
{
	struct llt_ndlc *ndlc;

	ndlc = devm_kzalloc(dev, sizeof(struct llt_ndlc), GFP_KERNEL);
	if (!ndlc)
		return -ENOMEM;

	ndlc->ops = phy_ops;
	ndlc->phy_id = phy_id;
	ndlc->dev = dev;
	ndlc->powered = 0;

	*ndlc_id = ndlc;

	/* initialize timers */
	timer_setup(&ndlc->t1_timer, ndlc_t1_timeout, 0);
	timer_setup(&ndlc->t2_timer, ndlc_t2_timeout, 0);

	skb_queue_head_init(&ndlc->rcv_q);
	skb_queue_head_init(&ndlc->send_q);
	skb_queue_head_init(&ndlc->ack_pending_q);

	INIT_WORK(&ndlc->sm_work, llt_ndlc_sm_work);

	return st_nci_probe(ndlc, phy_headroom, phy_tailroom, se_status);
}