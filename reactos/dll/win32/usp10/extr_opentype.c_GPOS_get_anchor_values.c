#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_9__ {int /*<<< orphan*/  AnchorFormat; int /*<<< orphan*/  YCoordinate; int /*<<< orphan*/  XCoordinate; } ;
struct TYPE_8__ {int /*<<< orphan*/  YCoordinate; int /*<<< orphan*/  XCoordinate; } ;
struct TYPE_7__ {int /*<<< orphan*/  YDeviceTable; int /*<<< orphan*/  XDeviceTable; int /*<<< orphan*/  YCoordinate; int /*<<< orphan*/  XCoordinate; } ;
struct TYPE_6__ {short x; short y; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  OT_DeviceTable ;
typedef  TYPE_2__ GPOS_AnchorFormat3 ;
typedef  TYPE_3__ GPOS_AnchorFormat2 ;
typedef  TYPE_4__ GPOS_AnchorFormat1 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 short GPOS_get_device_table_value (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static void GPOS_get_anchor_values(const void *table, POINT *pt, WORD ppem)
{
    const GPOS_AnchorFormat1* anchor1 = (const GPOS_AnchorFormat1*)table;

    switch (GET_BE_WORD(anchor1->AnchorFormat))
    {
        case 1:
        {
            TRACE("Anchor Format 1\n");
            pt->x = (short)GET_BE_WORD(anchor1->XCoordinate);
            pt->y = (short)GET_BE_WORD(anchor1->YCoordinate);
            break;
        }
        case 2:
        {
            const GPOS_AnchorFormat2* anchor2 = (const GPOS_AnchorFormat2*)table;
            TRACE("Anchor Format 2\n");
            pt->x = (short)GET_BE_WORD(anchor2->XCoordinate);
            pt->y = (short)GET_BE_WORD(anchor2->YCoordinate);
            break;
        }
        case 3:
        {
            int offset;
            const GPOS_AnchorFormat3* anchor3 = (const GPOS_AnchorFormat3*)table;
            TRACE("Anchor Format 3\n");
            pt->x = (short)GET_BE_WORD(anchor3->XCoordinate);
            pt->y = (short)GET_BE_WORD(anchor3->YCoordinate);
            offset = GET_BE_WORD(anchor3->XDeviceTable);
            TRACE("ppem %i\n",ppem);
            if (offset)
            {
                const OT_DeviceTable* DeviceTableX = NULL;
                DeviceTableX = (const OT_DeviceTable*)((const BYTE*)anchor3 + offset);
                pt->x += GPOS_get_device_table_value(DeviceTableX, ppem);
            }
            offset = GET_BE_WORD(anchor3->YDeviceTable);
            if (offset)
            {
                const OT_DeviceTable* DeviceTableY = NULL;
                DeviceTableY = (const OT_DeviceTable*)((const BYTE*)anchor3 + offset);
                pt->y += GPOS_get_device_table_value(DeviceTableY, ppem);
            }
            break;
        }
        default:
            ERR("Unknown Anchor Format %i\n",GET_BE_WORD(anchor1->AnchorFormat));
            pt->x = 0;
            pt->y = 0;
    }
}