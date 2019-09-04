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
struct TYPE_3__ {int /*<<< orphan*/  rssi_ant; } ;
struct TYPE_4__ {TYPE_1__ ant; } ;
struct rt2x00_dev {TYPE_2__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ewma_rssi_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00link_antenna_reset(struct rt2x00_dev *rt2x00dev)
{
	ewma_rssi_init(&rt2x00dev->link.ant.rssi_ant);
}