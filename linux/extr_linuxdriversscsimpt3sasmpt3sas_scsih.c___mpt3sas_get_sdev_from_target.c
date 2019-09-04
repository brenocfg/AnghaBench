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
struct _sas_device {int dummy; } ;
struct MPT3SAS_TARGET {struct _sas_device* sas_dev; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_device_get (struct _sas_device*) ; 

__attribute__((used)) static struct _sas_device *
__mpt3sas_get_sdev_from_target(struct MPT3SAS_ADAPTER *ioc,
		struct MPT3SAS_TARGET *tgt_priv)
{
	struct _sas_device *ret;

	assert_spin_locked(&ioc->sas_device_lock);

	ret = tgt_priv->sas_dev;
	if (ret)
		sas_device_get(ret);

	return ret;
}