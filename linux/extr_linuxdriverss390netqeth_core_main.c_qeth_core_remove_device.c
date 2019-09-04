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
struct qeth_card {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; TYPE_1__* discipline; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  rwlock; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* remove ) (struct ccwgroup_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 struct qeth_card* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 TYPE_2__ qeth_core_card_list ; 
 int /*<<< orphan*/  qeth_core_free_card (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_core_free_discipline (struct qeth_card*) ; 
 int /*<<< orphan*/  stub1 (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qeth_core_remove_device(struct ccwgroup_device *gdev)
{
	unsigned long flags;
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);

	QETH_DBF_TEXT(SETUP, 2, "removedv");

	if (card->discipline) {
		card->discipline->remove(gdev);
		qeth_core_free_discipline(card);
	}

	write_lock_irqsave(&qeth_core_card_list.rwlock, flags);
	list_del(&card->list);
	write_unlock_irqrestore(&qeth_core_card_list.rwlock, flags);
	free_netdev(card->dev);
	qeth_core_free_card(card);
	dev_set_drvdata(&gdev->dev, NULL);
	put_device(&gdev->dev);
}