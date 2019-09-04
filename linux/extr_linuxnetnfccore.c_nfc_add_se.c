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
typedef  int /*<<< orphan*/  u16 ;
struct nfc_se {int /*<<< orphan*/  list; int /*<<< orphan*/  state; int /*<<< orphan*/  type; int /*<<< orphan*/  idx; } ;
struct nfc_dev {int /*<<< orphan*/  secure_elements; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EALREADY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFC_SE_DISABLED ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfc_se*) ; 
 struct nfc_se* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nfc_se* nfc_find_se (struct nfc_dev*,int /*<<< orphan*/ ) ; 
 int nfc_genl_se_added (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nfc_add_se(struct nfc_dev *dev, u32 se_idx, u16 type)
{
	struct nfc_se *se;
	int rc;

	pr_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	se = nfc_find_se(dev, se_idx);
	if (se)
		return -EALREADY;

	se = kzalloc(sizeof(struct nfc_se), GFP_KERNEL);
	if (!se)
		return -ENOMEM;

	se->idx = se_idx;
	se->type = type;
	se->state = NFC_SE_DISABLED;
	INIT_LIST_HEAD(&se->list);

	list_add(&se->list, &dev->secure_elements);

	rc = nfc_genl_se_added(dev, se_idx, type);
	if (rc < 0) {
		list_del(&se->list);
		kfree(se);

		return rc;
	}

	return 0;
}