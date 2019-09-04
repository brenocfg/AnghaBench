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
struct nfc_hci_dev {int /*<<< orphan*/  quirks; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ST21NFCA_FACTORY_MODE ; 
#define  ST21NFCA_FACTORY_MODE_OFF 129 
#define  ST21NFCA_FACTORY_MODE_ON 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st21nfca_factory_mode(struct nfc_dev *dev, void *data,
			       size_t data_len)
{
	struct nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	if (data_len != 1)
		return -EINVAL;

	pr_debug("factory mode: %x\n", ((u8 *)data)[0]);

	switch (((u8 *)data)[0]) {
	case ST21NFCA_FACTORY_MODE_ON:
		test_and_set_bit(ST21NFCA_FACTORY_MODE, &hdev->quirks);
	break;
	case ST21NFCA_FACTORY_MODE_OFF:
		clear_bit(ST21NFCA_FACTORY_MODE, &hdev->quirks);
	break;
	default:
		return -EINVAL;
	}

	return 0;
}