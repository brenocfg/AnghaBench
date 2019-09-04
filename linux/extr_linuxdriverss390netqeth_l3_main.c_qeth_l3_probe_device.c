#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ hwtrap; } ;
struct TYPE_5__ {scalar_t__ layer2; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__ options; int /*<<< orphan*/  ip_mc_htable; int /*<<< orphan*/  ip_htable; } ;
struct TYPE_7__ {int /*<<< orphan*/ * type; } ;
struct ccwgroup_device {TYPE_3__ dev; } ;

/* Variables and functions */
 struct qeth_card* dev_get_drvdata (TYPE_3__*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_generic_devtype ; 
 int qeth_l3_create_device_attributes (TYPE_3__*) ; 

__attribute__((used)) static int qeth_l3_probe_device(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);
	int rc;

	if (gdev->dev.type == &qeth_generic_devtype) {
		rc = qeth_l3_create_device_attributes(&gdev->dev);
		if (rc)
			return rc;
	}
	hash_init(card->ip_htable);
	hash_init(card->ip_mc_htable);
	card->options.layer2 = 0;
	card->info.hwtrap = 0;
	return 0;
}