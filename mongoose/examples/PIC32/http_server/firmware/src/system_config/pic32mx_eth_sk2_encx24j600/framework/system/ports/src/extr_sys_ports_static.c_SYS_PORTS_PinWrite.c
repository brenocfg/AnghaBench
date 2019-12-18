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
typedef  int /*<<< orphan*/  PORTS_MODULE_ID ;
typedef  int /*<<< orphan*/  PORTS_CHANNEL ;
typedef  int /*<<< orphan*/  PORTS_BIT_POS ;

/* Variables and functions */
 int /*<<< orphan*/  PLIB_PORTS_PinWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void SYS_PORTS_PinWrite ( PORTS_MODULE_ID index,
                          PORTS_CHANNEL channel,
                          PORTS_BIT_POS bitPos,
                          bool value )
{
    PLIB_PORTS_PinWrite ( index, channel, bitPos, value );
}