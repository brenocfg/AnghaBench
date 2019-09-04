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
struct q6adm {int /*<<< orphan*/  copps_list_lock; int /*<<< orphan*/  copps_list; int /*<<< orphan*/  matrix_map_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  ainfo; struct device* dev; struct apr_device* apr; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct apr_device {int /*<<< orphan*/  svc_id; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct q6adm*) ; 
 struct q6adm* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  q6core_get_svc_api_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6adm_probe(struct apr_device *adev)
{
	struct device *dev = &adev->dev;
	struct q6adm *adm;

	adm = devm_kzalloc(&adev->dev, sizeof(*adm), GFP_KERNEL);
	if (!adm)
		return -ENOMEM;

	adm->apr = adev;
	dev_set_drvdata(&adev->dev, adm);
	adm->dev = dev;
	q6core_get_svc_api_info(adev->svc_id, &adm->ainfo);
	mutex_init(&adm->lock);
	init_waitqueue_head(&adm->matrix_map_wait);

	INIT_LIST_HEAD(&adm->copps_list);
	spin_lock_init(&adm->copps_list_lock);

	return of_platform_populate(dev->of_node, NULL, NULL, dev);
}