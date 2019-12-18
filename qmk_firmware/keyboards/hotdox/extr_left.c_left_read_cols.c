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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCP23017_B0_GPIOA ; 
 int /*<<< orphan*/  left_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint8_t left_read_cols(void)
{
    uint8_t data = 0;

    left_read(MCP23017_B0_GPIOA, &data);

    return data;
}