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
struct mtk_eth {struct mt7620_gsw* sw_priv; } ;
struct mt7620_gsw {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mtk_speed_str (int) ; 

void mt7620_print_link_state(struct mtk_eth *eth, int port, int link,
			     int speed, int duplex)
{
	struct mt7620_gsw *gsw = eth->sw_priv;

	if (link)
		dev_info(gsw->dev, "port %d link up (%sMbps/%s duplex)\n",
			 port, mtk_speed_str(speed),
			 (duplex) ? "Full" : "Half");
	else
		dev_info(gsw->dev, "port %d link down\n", port);
}