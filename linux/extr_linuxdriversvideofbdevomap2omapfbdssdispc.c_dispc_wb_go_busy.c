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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONTROL2 ; 
 int REG_GET (int /*<<< orphan*/ ,int,int) ; 

bool dispc_wb_go_busy(void)
{
	return REG_GET(DISPC_CONTROL2, 6, 6) == 1;
}