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
struct ufshcd_dme_attr_val {int /*<<< orphan*/  peer; int /*<<< orphan*/  mib_val; int /*<<< orphan*/  attr_sel; } ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SET_NOR ; 
 int ufshcd_dme_set_attr (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ufshcd_dwc_dme_set_attrs(struct ufs_hba *hba,
				const struct ufshcd_dme_attr_val *v, int n)
{
	int ret = 0;
	int attr_node = 0;

	for (attr_node = 0; attr_node < n; attr_node++) {
		ret = ufshcd_dme_set_attr(hba, v[attr_node].attr_sel,
			ATTR_SET_NOR, v[attr_node].mib_val, v[attr_node].peer);

		if (ret)
			return ret;
	}

	return 0;
}