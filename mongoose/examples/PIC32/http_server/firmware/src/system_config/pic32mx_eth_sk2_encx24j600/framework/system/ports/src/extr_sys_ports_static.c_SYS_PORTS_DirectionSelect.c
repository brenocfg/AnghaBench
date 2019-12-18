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
typedef  int /*<<< orphan*/  PORTS_DATA_MASK ;
typedef  int /*<<< orphan*/  PORTS_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  PLIB_PORTS_DirectionInputSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_PORTS_DirectionOutputSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SYS_PORTS_DIRECTION_INPUT ; 

void SYS_PORTS_DirectionSelect( PORTS_MODULE_ID index,
                             SYS_PORTS_PIN_DIRECTION pinDir,
                             PORTS_CHANNEL channel,
                             PORTS_DATA_MASK mask )
{
    if (pinDir == SYS_PORTS_DIRECTION_INPUT)
    {
        PLIB_PORTS_DirectionInputSet(index, channel, mask);
    }
    else
    {
        PLIB_PORTS_DirectionOutputSet(index, channel, mask);
    }
}