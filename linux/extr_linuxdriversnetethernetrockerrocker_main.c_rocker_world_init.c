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
struct rocker_world_ops {int (* init ) (struct rocker*) ;int /*<<< orphan*/  priv_size; } ;
struct rocker {int /*<<< orphan*/  wpriv; struct rocker_world_ops* wops; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rocker_world_ops* rocker_world_ops_find (int /*<<< orphan*/ ) ; 
 int stub1 (struct rocker*) ; 

__attribute__((used)) static int rocker_world_init(struct rocker *rocker, u8 mode)
{
	struct rocker_world_ops *wops;
	int err;

	wops = rocker_world_ops_find(mode);
	if (!wops) {
		dev_err(&rocker->pdev->dev, "port mode \"%d\" is not supported\n",
			mode);
		return -EINVAL;
	}
	rocker->wops = wops;
	rocker->wpriv = kzalloc(wops->priv_size, GFP_KERNEL);
	if (!rocker->wpriv)
		return -ENOMEM;
	if (!wops->init)
		return 0;
	err = wops->init(rocker);
	if (err)
		kfree(rocker->wpriv);
	return err;
}