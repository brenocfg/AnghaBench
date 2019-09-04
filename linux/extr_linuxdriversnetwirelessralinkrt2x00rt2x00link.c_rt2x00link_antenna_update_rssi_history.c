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
struct link_ant {int rssi_history; } ;
struct TYPE_2__ {struct link_ant ant; } ;
struct rt2x00_dev {TYPE_1__ link; } ;

/* Variables and functions */

__attribute__((used)) static void rt2x00link_antenna_update_rssi_history(struct rt2x00_dev *rt2x00dev,
						   int rssi)
{
	struct link_ant *ant = &rt2x00dev->link.ant;
	ant->rssi_history = rssi;
}