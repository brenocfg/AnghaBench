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
struct TYPE_2__ {int nr_cooling_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG_DEV_ROWS ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 TYPE_1__ ptdata ; 

__attribute__((used)) static int diag_dev_rows(void)
{
	int entries = ptdata.nr_cooling_dev + 1;
	int rows = max(DIAG_DEV_ROWS, (entries + 1) / 2);
	return min(rows, entries);
}