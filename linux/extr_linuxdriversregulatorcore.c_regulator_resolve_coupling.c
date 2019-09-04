#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n_coupled; int /*<<< orphan*/  n_resolved; struct regulator_dev** coupled_rdevs; } ;
struct regulator_dev {TYPE_2__* constraints; TYPE_1__ coupling_desc; } ;
struct TYPE_4__ {scalar_t__ max_spread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MAX_COUPLED ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_VOLTAGE ; 
 int /*<<< orphan*/  of_check_coupling_data (struct regulator_dev*) ; 
 int of_get_n_coupled (struct regulator_dev*) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*) ; 
 int /*<<< orphan*/  regulator_fill_coupling_array (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regulator_resolve_coupling(struct regulator_dev *rdev)
{
	int n_phandles;

	if (!IS_ENABLED(CONFIG_OF))
		n_phandles = 0;
	else
		n_phandles = of_get_n_coupled(rdev);

	if (n_phandles + 1 > MAX_COUPLED) {
		rdev_err(rdev, "too many regulators coupled\n");
		return -EPERM;
	}

	/*
	 * Every regulator should always have coupling descriptor filled with
	 * at least pointer to itself.
	 */
	rdev->coupling_desc.coupled_rdevs[0] = rdev;
	rdev->coupling_desc.n_coupled = n_phandles + 1;
	rdev->coupling_desc.n_resolved++;

	/* regulator isn't coupled */
	if (n_phandles == 0)
		return 0;

	/* regulator, which can't change its voltage, can't be coupled */
	if (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE)) {
		rdev_err(rdev, "voltage operation not allowed\n");
		return -EPERM;
	}

	if (rdev->constraints->max_spread <= 0) {
		rdev_err(rdev, "wrong max_spread value\n");
		return -EPERM;
	}

	if (!of_check_coupling_data(rdev))
		return -EPERM;

	/*
	 * After everything has been checked, try to fill rdevs array
	 * with pointers to regulators parsed from device tree. If some
	 * regulators are not registered yet, retry in late init call
	 */
	regulator_fill_coupling_array(rdev);

	return 0;
}