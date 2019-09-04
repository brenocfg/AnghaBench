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
struct serdev_device {int dummy; } ;
struct qcauart {int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct qcauart* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static void qca_tty_wakeup(struct serdev_device *serdev)
{
	struct qcauart *qca = serdev_device_get_drvdata(serdev);

	schedule_work(&qca->tx_work);
}