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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  CLK_BUSES_PERIPHERAL ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CLK_BUS_PERIPHERAL_1 ; 

inline uint32_t SYS_CLK_PeripheralFrequencyGet ( CLK_BUSES_PERIPHERAL peripheralBus )
{
    return SYS_CLK_BUS_PERIPHERAL_1;
}