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
typedef  scalar_t__ SYS_PORTS_PIN_DIRECTION ;
typedef  int /*<<< orphan*/  PORTS_MODULE_ID ;
typedef  int /*<<< orphan*/  PORTS_CHANNEL ;
typedef  int /*<<< orphan*/  PORTS_BIT_POS ;

/* Variables and functions */
 int /*<<< orphan*/  PLIB_PORTS_PinDirectionInputSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_PinDirectionOutputSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SYS_PORTS_DIRECTION_OUTPUT ; 

void SYS_PORTS_PinDirectionSelect ( PORTS_MODULE_ID index,
                                 SYS_PORTS_PIN_DIRECTION pinDir,
                                 PORTS_CHANNEL channel,
                                 PORTS_BIT_POS bitPos )
{
    if (pinDir == SYS_PORTS_DIRECTION_OUTPUT)
    {
        PLIB_PORTS_PinDirectionOutputSet(index, channel, bitPos);
    }
    else
    {
        PLIB_PORTS_PinDirectionInputSet(index, channel, bitPos);
    }
}