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
 int /*<<< orphan*/  MCP23017_B0_IODIRB ; 
 int /*<<< orphan*/  left_write (int /*<<< orphan*/ ,int) ; 

void left_unselect_rows(void)
{
    left_write(MCP23017_B0_IODIRB, 0x3F);
}