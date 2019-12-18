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
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  MACHVTBL ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HalpCalibrateStallExecution () ; 
 int /*<<< orphan*/  MachVtbl ; 
 int /*<<< orphan*/  PcMachInit (char const*) ; 
 int READ_PORT_ULONG (int*) ; 
 int /*<<< orphan*/  WRITE_PORT_ULONG (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XboxMachInit (char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

VOID
MachInit(const char *CmdLine)
{
    ULONG PciId;

    memset(&MachVtbl, 0, sizeof(MACHVTBL));

    /* Check for Xbox by identifying device at PCI 0:0:0, if it's
     * 0x10de/0x02a5 then we're running on an Xbox */
    WRITE_PORT_ULONG((ULONG*)0xcf8, CONFIG_CMD(0, 0, 0));
    PciId = READ_PORT_ULONG((ULONG*)0xcfc);
    if (PciId == 0x02a510de)
    {
        XboxMachInit(CmdLine);
    }
    else
    {
        PcMachInit(CmdLine);
    }

    HalpCalibrateStallExecution();
}