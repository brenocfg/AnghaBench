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
typedef  int /*<<< orphan*/  PORTS_REMAP_INPUT_PIN ;
typedef  int /*<<< orphan*/  PORTS_REMAP_INPUT_FUNCTION ;
typedef  int /*<<< orphan*/  PORTS_MODULE_ID ;

/* Variables and functions */

void SYS_PORTS_RemapInput( PORTS_MODULE_ID      index,
						   PORTS_REMAP_INPUT_FUNCTION function,
						   PORTS_REMAP_INPUT_PIN      remapPin )
{
#if defined(PLIB_PORTS_ExistsRemapInput)
    if(PLIB_PORTS_ExistsRemapInput(index))
    {
        PLIB_DEVCON_SystemUnlock(DEVCON_ID_0);
        PLIB_DEVCON_DeviceRegistersUnlock(DEVCON_ID_0, DEVCON_PPS_REGISTERS);
        PLIB_PORTS_RemapInput( index, function, remapPin);
    }
#endif
}