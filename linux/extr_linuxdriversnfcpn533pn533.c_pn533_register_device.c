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
typedef  int /*<<< orphan*/  u32 ;
struct pn533_phy_ops {int dummy; } ;
struct pn533_frame_ops {int /*<<< orphan*/  tx_tail_len; scalar_t__ tx_header_len; } ;
struct pn533 {int protocol_type; int /*<<< orphan*/ * wq; int /*<<< orphan*/  nfc_dev; struct pn533_frame_ops* ops; int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  fragment_skb; int /*<<< orphan*/  resp_q; int /*<<< orphan*/  listen_timer; int /*<<< orphan*/  rf_work; int /*<<< orphan*/  poll_work; int /*<<< orphan*/  mi_tm_tx_work; int /*<<< orphan*/  mi_tm_rx_work; int /*<<< orphan*/  tg_work; int /*<<< orphan*/  mi_tx_work; int /*<<< orphan*/  mi_rx_work; int /*<<< orphan*/  cmd_complete_work; int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  device_type; struct device* dev; struct pn533_phy_ops* phy_ops; void* phy; } ;
struct device {int dummy; } ;
typedef  enum pn533_protocol_type { ____Placeholder_pn533_protocol_type } pn533_protocol_type ;

/* Variables and functions */
 int ENOMEM ; 
 struct pn533* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PN533_CMD_DATAEXCH_HEAD_LEN ; 
 int /*<<< orphan*/ * alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pn533*) ; 
 struct pn533* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_allocate_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_free_device (int /*<<< orphan*/ ) ; 
 int nfc_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_set_drvdata (int /*<<< orphan*/ ,struct pn533*) ; 
 int /*<<< orphan*/  nfc_set_parent_dev (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  pn533_listen_mode_timer ; 
 int /*<<< orphan*/  pn533_nfc_ops ; 
 struct pn533_frame_ops pn533_std_frame_ops ; 
 int /*<<< orphan*/  pn533_wq_cmd ; 
 int /*<<< orphan*/  pn533_wq_cmd_complete ; 
 int /*<<< orphan*/  pn533_wq_mi_recv ; 
 int /*<<< orphan*/  pn533_wq_mi_send ; 
 int /*<<< orphan*/  pn533_wq_poll ; 
 int /*<<< orphan*/  pn533_wq_rf ; 
 int /*<<< orphan*/  pn533_wq_tg_get_data ; 
 int /*<<< orphan*/  pn533_wq_tm_mi_recv ; 
 int /*<<< orphan*/  pn533_wq_tm_mi_send ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct pn533 *pn533_register_device(u32 device_type,
				u32 protocols,
				enum pn533_protocol_type protocol_type,
				void *phy,
				struct pn533_phy_ops *phy_ops,
				struct pn533_frame_ops *fops,
				struct device *dev,
				struct device *parent)
{
	struct pn533 *priv;
	int rc = -ENOMEM;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return ERR_PTR(-ENOMEM);

	priv->phy = phy;
	priv->phy_ops = phy_ops;
	priv->dev = dev;
	if (fops != NULL)
		priv->ops = fops;
	else
		priv->ops = &pn533_std_frame_ops;

	priv->protocol_type = protocol_type;
	priv->device_type = device_type;

	mutex_init(&priv->cmd_lock);

	INIT_WORK(&priv->cmd_work, pn533_wq_cmd);
	INIT_WORK(&priv->cmd_complete_work, pn533_wq_cmd_complete);
	INIT_WORK(&priv->mi_rx_work, pn533_wq_mi_recv);
	INIT_WORK(&priv->mi_tx_work, pn533_wq_mi_send);
	INIT_WORK(&priv->tg_work, pn533_wq_tg_get_data);
	INIT_WORK(&priv->mi_tm_rx_work, pn533_wq_tm_mi_recv);
	INIT_WORK(&priv->mi_tm_tx_work, pn533_wq_tm_mi_send);
	INIT_DELAYED_WORK(&priv->poll_work, pn533_wq_poll);
	INIT_WORK(&priv->rf_work, pn533_wq_rf);
	priv->wq = alloc_ordered_workqueue("pn533", 0);
	if (priv->wq == NULL)
		goto error;

	timer_setup(&priv->listen_timer, pn533_listen_mode_timer, 0);

	skb_queue_head_init(&priv->resp_q);
	skb_queue_head_init(&priv->fragment_skb);

	INIT_LIST_HEAD(&priv->cmd_queue);

	priv->nfc_dev = nfc_allocate_device(&pn533_nfc_ops, protocols,
					   priv->ops->tx_header_len +
					   PN533_CMD_DATAEXCH_HEAD_LEN,
					   priv->ops->tx_tail_len);
	if (!priv->nfc_dev) {
		rc = -ENOMEM;
		goto destroy_wq;
	}

	nfc_set_parent_dev(priv->nfc_dev, parent);
	nfc_set_drvdata(priv->nfc_dev, priv);

	rc = nfc_register_device(priv->nfc_dev);
	if (rc)
		goto free_nfc_dev;

	return priv;

free_nfc_dev:
	nfc_free_device(priv->nfc_dev);

destroy_wq:
	destroy_workqueue(priv->wq);
error:
	kfree(priv);
	return ERR_PTR(rc);
}