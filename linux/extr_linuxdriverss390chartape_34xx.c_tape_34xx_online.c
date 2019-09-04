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
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_discipline_34xx ; 
 int tape_generic_online (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tape_34xx_online(struct ccw_device *cdev)
{
	return tape_generic_online(
		dev_get_drvdata(&cdev->dev),
		&tape_discipline_34xx
	);
}