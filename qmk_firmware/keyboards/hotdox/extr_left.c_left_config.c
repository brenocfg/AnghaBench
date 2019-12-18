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
 int /*<<< orphan*/  MCP23017_B0_GPIOB ; 
 int /*<<< orphan*/  MCP23017_B0_GPPUA ; 
 int /*<<< orphan*/  MCP23017_B0_IODIRA ; 
 int /*<<< orphan*/  MCP23017_B0_IODIRB ; 
 int /*<<< orphan*/  MCP23017_B0_IPOLA ; 
 int /*<<< orphan*/  left_write (int /*<<< orphan*/ ,int) ; 

void left_config(void)
{
  left_write(MCP23017_B0_IODIRA, 0x7F);
  left_write(MCP23017_B0_IPOLA,  0x7F);
  left_write(MCP23017_B0_GPPUA,  0x7F);

  left_write(MCP23017_B0_IODIRB, 0xFF);
  left_write(MCP23017_B0_GPIOB,  0xC0);
}