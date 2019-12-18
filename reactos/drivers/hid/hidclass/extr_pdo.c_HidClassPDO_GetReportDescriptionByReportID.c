#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_6__ {size_t ReportIDsLength; TYPE_1__* ReportIDs; } ;
struct TYPE_5__ {scalar_t__ ReportID; } ;
typedef  TYPE_1__* PHIDP_REPORT_IDS ;
typedef  TYPE_2__* PHIDP_DEVICE_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 

PHIDP_REPORT_IDS
HidClassPDO_GetReportDescriptionByReportID(
    PHIDP_DEVICE_DESC DeviceDescription,
    UCHAR ReportID)
{
    ULONG Index;

    for (Index = 0; Index < DeviceDescription->ReportIDsLength; Index++)
    {
        if (DeviceDescription->ReportIDs[Index].ReportID == ReportID)
        {
            //
            // found report id
            //
            return &DeviceDescription->ReportIDs[Index];
        }
    }

    //
    // failed to find report id
    //
    DPRINT1("[HIDCLASS] GetReportDescriptionByReportID ReportID %x not found\n", ReportID);
    ASSERT(FALSE);
    return NULL;
}