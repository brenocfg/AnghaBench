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
struct phy_device {int link; scalar_t__ asym_pause; scalar_t__ pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  SPEED_100 ; 

__attribute__((used)) static int ip17xx_read_status(struct phy_device *pdev)
{
	pdev->speed = SPEED_100;
	pdev->duplex = DUPLEX_FULL;
	pdev->pause = pdev->asym_pause = 0;
	pdev->link = 1;

	return 0;
}