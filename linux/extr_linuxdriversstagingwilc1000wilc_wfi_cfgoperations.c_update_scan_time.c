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
struct TYPE_2__ {int /*<<< orphan*/  time_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int last_scanned_cnt ; 
 TYPE_1__* last_scanned_shadow ; 

__attribute__((used)) static void update_scan_time(void)
{
	int i;

	for (i = 0; i < last_scanned_cnt; i++)
		last_scanned_shadow[i].time_scan = jiffies;
}