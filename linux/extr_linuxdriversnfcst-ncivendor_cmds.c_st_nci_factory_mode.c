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
typedef  int u8 ;
struct st_nci_info {int /*<<< orphan*/  flags; } ;
struct nfc_dev {int dummy; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ST_NCI_FACTORY_MODE ; 
#define  ST_NCI_FACTORY_MODE_OFF 129 
#define  ST_NCI_FACTORY_MODE_ON 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_nci_factory_mode(struct nfc_dev *dev, void *data,
			       size_t data_len)
{
	struct nci_dev *ndev = nfc_get_drvdata(dev);
	struct st_nci_info *info = nci_get_drvdata(ndev);

	if (data_len != 1)
		return -EINVAL;

	pr_debug("factory mode: %x\n", ((u8 *)data)[0]);

	switch (((u8 *)data)[0]) {
	case ST_NCI_FACTORY_MODE_ON:
		test_and_set_bit(ST_NCI_FACTORY_MODE, &info->flags);
	break;
	case ST_NCI_FACTORY_MODE_OFF:
		clear_bit(ST_NCI_FACTORY_MODE, &info->flags);
	break;
	default:
		return -EINVAL;
	}

	return 0;
}