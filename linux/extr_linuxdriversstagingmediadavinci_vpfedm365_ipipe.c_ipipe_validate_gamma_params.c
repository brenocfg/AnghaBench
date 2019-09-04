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
struct vpfe_ipipe_gamma {int bypass_r; int bypass_b; int bypass_g; scalar_t__ tbl_sel; int tbl_size; int /*<<< orphan*/  table_g; int /*<<< orphan*/  table_b; int /*<<< orphan*/  table_r; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VPFE_IPIPE_GAMMA_TBL_RAM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int ipipe_validate_gamma_entry (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ipipe_validate_gamma_params(struct vpfe_ipipe_gamma *gamma, struct device *dev)
{
	int table_size;
	int err;

	if (gamma->bypass_r > 1 ||
	    gamma->bypass_b > 1 ||
	    gamma->bypass_g > 1)
		return -EINVAL;

	if (gamma->tbl_sel != VPFE_IPIPE_GAMMA_TBL_RAM)
		return 0;

	table_size = gamma->tbl_size;
	if (!gamma->bypass_r) {
		err = ipipe_validate_gamma_entry(gamma->table_r, table_size);
		if (err) {
			dev_err(dev, "GAMMA R - table entry invalid\n");
			return err;
		}
	}

	if (!gamma->bypass_b) {
		err = ipipe_validate_gamma_entry(gamma->table_b, table_size);
		if (err) {
			dev_err(dev, "GAMMA B - table entry invalid\n");
			return err;
		}
	}

	if (!gamma->bypass_g) {
		err = ipipe_validate_gamma_entry(gamma->table_g, table_size);
		if (err) {
			dev_err(dev, "GAMMA G - table entry invalid\n");
			return err;
		}
	}

	return 0;
}