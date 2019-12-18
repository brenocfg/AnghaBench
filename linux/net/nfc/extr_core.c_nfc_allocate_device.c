#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nfc_ops {scalar_t__ check_presence; int /*<<< orphan*/  im_transceive; int /*<<< orphan*/  deactivate_target; int /*<<< orphan*/  activate_target; int /*<<< orphan*/  stop_poll; int /*<<< orphan*/  start_poll; } ;
struct TYPE_3__ {int /*<<< orphan*/ * class; } ;
struct nfc_dev {int idx; int tx_headroom; int tx_tailroom; int targets_generation; int /*<<< orphan*/  check_pres_work; int /*<<< orphan*/  check_pres_timer; int /*<<< orphan*/  rf_mode; int /*<<< orphan*/  genl_data; int /*<<< orphan*/  secure_elements; scalar_t__ supported_protocols; struct nfc_ops* ops; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFC_RF_NONE ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfc_dev*) ; 
 struct nfc_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_check_pres_timeout ; 
 int /*<<< orphan*/  nfc_check_pres_work ; 
 int /*<<< orphan*/  nfc_class ; 
 int /*<<< orphan*/  nfc_genl_data_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_index_ida ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct nfc_dev *nfc_allocate_device(struct nfc_ops *ops,
				    u32 supported_protocols,
				    int tx_headroom, int tx_tailroom)
{
	struct nfc_dev *dev;
	int rc;

	if (!ops->start_poll || !ops->stop_poll || !ops->activate_target ||
	    !ops->deactivate_target || !ops->im_transceive)
		return NULL;

	if (!supported_protocols)
		return NULL;

	dev = kzalloc(sizeof(struct nfc_dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	rc = ida_simple_get(&nfc_index_ida, 0, 0, GFP_KERNEL);
	if (rc < 0)
		goto err_free_dev;
	dev->idx = rc;

	dev->dev.class = &nfc_class;
	dev_set_name(&dev->dev, "nfc%d", dev->idx);
	device_initialize(&dev->dev);

	dev->ops = ops;
	dev->supported_protocols = supported_protocols;
	dev->tx_headroom = tx_headroom;
	dev->tx_tailroom = tx_tailroom;
	INIT_LIST_HEAD(&dev->secure_elements);

	nfc_genl_data_init(&dev->genl_data);

	dev->rf_mode = NFC_RF_NONE;

	/* first generation must not be 0 */
	dev->targets_generation = 1;

	if (ops->check_presence) {
		timer_setup(&dev->check_pres_timer, nfc_check_pres_timeout, 0);
		INIT_WORK(&dev->check_pres_work, nfc_check_pres_work);
	}

	return dev;

err_free_dev:
	kfree(dev);

	return NULL;
}