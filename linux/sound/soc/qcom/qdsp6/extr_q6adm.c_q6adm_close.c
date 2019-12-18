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
struct q6copp {int /*<<< orphan*/  refcount; int /*<<< orphan*/  copp_idx; int /*<<< orphan*/  afe_port; } ;
struct q6adm {int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct q6adm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int q6adm_device_close (struct q6adm*,struct q6copp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6adm_free_copp ; 

int q6adm_close(struct device *dev, struct q6copp *copp)
{
	struct q6adm *adm = dev_get_drvdata(dev->parent);
	int ret = 0;

	ret = q6adm_device_close(adm, copp, copp->afe_port, copp->copp_idx);
	if (ret < 0) {
		dev_err(adm->dev, "Failed to close copp %d\n", ret);
		return ret;
	}

	kref_put(&copp->refcount, q6adm_free_copp);

	return 0;
}