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
struct qeth_card {TYPE_1__* discipline; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* set_offline ) (struct ccwgroup_device*) ;} ;

/* Variables and functions */
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int stub1 (struct ccwgroup_device*) ; 

__attribute__((used)) static int qeth_core_set_offline(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);
	return card->discipline->set_offline(gdev);
}