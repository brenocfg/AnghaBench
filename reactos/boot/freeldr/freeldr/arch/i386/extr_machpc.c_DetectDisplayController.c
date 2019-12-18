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
typedef  int USHORT ;
typedef  int /*<<< orphan*/  PCONFIGURATION_COMPONENT_DATA ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ BiosIsVesaDdcSupported () ; 
 int BiosIsVesaSupported () ; 
 scalar_t__ BiosVesaReadEdid () ; 
 int /*<<< orphan*/  ControllerClass ; 
 int /*<<< orphan*/  DisplayController ; 
 int /*<<< orphan*/  FldrCreateComponentKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static VOID
DetectDisplayController(PCONFIGURATION_COMPONENT_DATA BusKey)
{
    CHAR Buffer[80];
    PCONFIGURATION_COMPONENT_DATA ControllerKey;
    USHORT VesaVersion;

    /* FIXME: Set 'ComponentInformation' value */

    VesaVersion = BiosIsVesaSupported();
    if (VesaVersion != 0)
    {
        TRACE("VESA version %c.%c\n",
              (VesaVersion >> 8) + '0',
              (VesaVersion & 0xFF) + '0');
    }
    else
    {
        TRACE("VESA not supported\n");
    }

    if (VesaVersion >= 0x0200)
    {
        strcpy(Buffer, "VBE Display");
    }
    else
    {
        strcpy(Buffer, "VGA Display");
    }

    FldrCreateComponentKey(BusKey,
                           ControllerClass,
                           DisplayController,
                           0x0,
                           0x0,
                           0xFFFFFFFF,
                           Buffer,
                           NULL,
                           0,
                           &ControllerKey);
    TRACE("Created key: DisplayController\\0\n");

    /* FIXME: Add display peripheral (monitor) data */
    if (VesaVersion != 0)
    {
        if (BiosIsVesaDdcSupported())
        {
            TRACE("VESA/DDC supported!\n");
            if (BiosVesaReadEdid())
            {
                TRACE("EDID data read successfully!\n");

            }
        }
    }
}