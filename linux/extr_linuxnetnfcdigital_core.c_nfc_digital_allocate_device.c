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
struct nfc_digital_ops {int /*<<< orphan*/  tg_get_rf_tech; scalar_t__ tg_listen_md; int /*<<< orphan*/  switch_rf; int /*<<< orphan*/  abort_cmd; int /*<<< orphan*/  tg_send_cmd; int /*<<< orphan*/  tg_configure_hw; int /*<<< orphan*/  tg_listen; int /*<<< orphan*/  in_send_cmd; int /*<<< orphan*/  in_configure_hw; } ;
struct nfc_digital_dev {int driver_capabilities; int protocols; int /*<<< orphan*/  nfc_dev; scalar_t__ tx_tailroom; scalar_t__ tx_headroom; int /*<<< orphan*/  poll_work; int /*<<< orphan*/  poll_lock; int /*<<< orphan*/  cmd_complete_work; int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  cmd_lock; struct nfc_digital_ops* ops; } ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ DIGITAL_CRC_LEN ; 
 scalar_t__ DIGITAL_MAX_HEADER_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NFC_PROTO_FELICA_MASK ; 
 int NFC_PROTO_ISO14443_B_MASK ; 
 int NFC_PROTO_ISO14443_MASK ; 
 int NFC_PROTO_ISO15693_MASK ; 
 int NFC_PROTO_JEWEL_MASK ; 
 int NFC_PROTO_MIFARE_MASK ; 
 int NFC_PROTO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  digital_nfc_ops ; 
 int /*<<< orphan*/  digital_wq_cmd ; 
 int /*<<< orphan*/  digital_wq_cmd_complete ; 
 int /*<<< orphan*/  digital_wq_poll ; 
 int /*<<< orphan*/  kfree (struct nfc_digital_dev*) ; 
 struct nfc_digital_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_allocate_device (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  nfc_set_drvdata (int /*<<< orphan*/ ,struct nfc_digital_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct nfc_digital_dev *nfc_digital_allocate_device(struct nfc_digital_ops *ops,
					    __u32 supported_protocols,
					    __u32 driver_capabilities,
					    int tx_headroom, int tx_tailroom)
{
	struct nfc_digital_dev *ddev;

	if (!ops->in_configure_hw || !ops->in_send_cmd || !ops->tg_listen ||
	    !ops->tg_configure_hw || !ops->tg_send_cmd || !ops->abort_cmd ||
	    !ops->switch_rf || (ops->tg_listen_md && !ops->tg_get_rf_tech))
		return NULL;

	ddev = kzalloc(sizeof(*ddev), GFP_KERNEL);
	if (!ddev)
		return NULL;

	ddev->driver_capabilities = driver_capabilities;
	ddev->ops = ops;

	mutex_init(&ddev->cmd_lock);
	INIT_LIST_HEAD(&ddev->cmd_queue);

	INIT_WORK(&ddev->cmd_work, digital_wq_cmd);
	INIT_WORK(&ddev->cmd_complete_work, digital_wq_cmd_complete);

	mutex_init(&ddev->poll_lock);
	INIT_DELAYED_WORK(&ddev->poll_work, digital_wq_poll);

	if (supported_protocols & NFC_PROTO_JEWEL_MASK)
		ddev->protocols |= NFC_PROTO_JEWEL_MASK;
	if (supported_protocols & NFC_PROTO_MIFARE_MASK)
		ddev->protocols |= NFC_PROTO_MIFARE_MASK;
	if (supported_protocols & NFC_PROTO_FELICA_MASK)
		ddev->protocols |= NFC_PROTO_FELICA_MASK;
	if (supported_protocols & NFC_PROTO_NFC_DEP_MASK)
		ddev->protocols |= NFC_PROTO_NFC_DEP_MASK;
	if (supported_protocols & NFC_PROTO_ISO15693_MASK)
		ddev->protocols |= NFC_PROTO_ISO15693_MASK;
	if (supported_protocols & NFC_PROTO_ISO14443_MASK)
		ddev->protocols |= NFC_PROTO_ISO14443_MASK;
	if (supported_protocols & NFC_PROTO_ISO14443_B_MASK)
		ddev->protocols |= NFC_PROTO_ISO14443_B_MASK;

	ddev->tx_headroom = tx_headroom + DIGITAL_MAX_HEADER_LEN;
	ddev->tx_tailroom = tx_tailroom + DIGITAL_CRC_LEN;

	ddev->nfc_dev = nfc_allocate_device(&digital_nfc_ops, ddev->protocols,
					    ddev->tx_headroom,
					    ddev->tx_tailroom);
	if (!ddev->nfc_dev) {
		pr_err("nfc_allocate_device failed\n");
		goto free_dev;
	}

	nfc_set_drvdata(ddev->nfc_dev, ddev);

	return ddev;

free_dev:
	kfree(ddev);

	return NULL;
}