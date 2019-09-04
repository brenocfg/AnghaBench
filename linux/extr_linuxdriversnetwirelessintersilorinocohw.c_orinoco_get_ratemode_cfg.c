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
struct TYPE_2__ {int bitrate; int automatic; } ;

/* Variables and functions */
 int BITRATE_TABLE_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* bitrate_table ; 

void orinoco_get_ratemode_cfg(int ratemode, int *bitrate, int *automatic)
{
	BUG_ON((ratemode < 0) || (ratemode >= BITRATE_TABLE_SIZE));

	*bitrate = bitrate_table[ratemode].bitrate * 100000;
	*automatic = bitrate_table[ratemode].automatic;
}