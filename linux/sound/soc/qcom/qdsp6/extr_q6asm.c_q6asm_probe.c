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
struct q6asm {int /*<<< orphan*/  slock; int /*<<< orphan*/  mem_wait; struct apr_device* adev; struct device* dev; int /*<<< orphan*/  ainfo; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct apr_device {int /*<<< orphan*/  svc_id; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct q6asm*) ; 
 struct q6asm* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  q6core_get_svc_api_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int q6asm_probe(struct apr_device *adev)
{
	struct device *dev = &adev->dev;
	struct q6asm *q6asm;

	q6asm = devm_kzalloc(dev, sizeof(*q6asm), GFP_KERNEL);
	if (!q6asm)
		return -ENOMEM;

	q6core_get_svc_api_info(adev->svc_id, &q6asm->ainfo);

	q6asm->dev = dev;
	q6asm->adev = adev;
	init_waitqueue_head(&q6asm->mem_wait);
	spin_lock_init(&q6asm->slock);
	dev_set_drvdata(dev, q6asm);

	return of_platform_populate(dev->of_node, NULL, NULL, dev);
}