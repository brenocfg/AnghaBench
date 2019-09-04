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
struct _pcie_device {int dummy; } ;
struct MPT3SAS_TARGET {struct _pcie_device* pcie_dev; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  pcie_device_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_device_get (struct _pcie_device*) ; 

__attribute__((used)) static struct _pcie_device *
__mpt3sas_get_pdev_from_target(struct MPT3SAS_ADAPTER *ioc,
	struct MPT3SAS_TARGET *tgt_priv)
{
	struct _pcie_device *ret;

	assert_spin_locked(&ioc->pcie_device_lock);

	ret = tgt_priv->pcie_dev;
	if (ret)
		pcie_device_get(ret);

	return ret;
}