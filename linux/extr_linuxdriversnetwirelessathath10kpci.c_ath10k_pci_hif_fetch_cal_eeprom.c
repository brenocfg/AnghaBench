#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {size_t cal_data_len; } ;
struct ath10k {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QCA_REV_9887 (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_enable_eeprom (struct ath10k*) ; 
 int ath10k_pci_read_eeprom (struct ath10k*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_pci_validate_cal (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_pci_hif_fetch_cal_eeprom(struct ath10k *ar, void **data,
					   size_t *data_len)
{
	u8 *caldata = NULL;
	size_t calsize, i;
	int ret;

	if (!QCA_REV_9887(ar))
		return -EOPNOTSUPP;

	calsize = ar->hw_params.cal_data_len;
	caldata = kmalloc(calsize, GFP_KERNEL);
	if (!caldata)
		return -ENOMEM;

	ath10k_pci_enable_eeprom(ar);

	for (i = 0; i < calsize; i++) {
		ret = ath10k_pci_read_eeprom(ar, i, &caldata[i]);
		if (ret)
			goto err_free;
	}

	if (!ath10k_pci_validate_cal(caldata, calsize))
		goto err_free;

	*data = caldata;
	*data_len = calsize;

	return 0;

err_free:
	kfree(caldata);

	return -EINVAL;
}