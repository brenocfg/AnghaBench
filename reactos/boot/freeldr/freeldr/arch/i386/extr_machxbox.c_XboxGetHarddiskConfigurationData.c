#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_18__ {int /*<<< orphan*/  Heads; int /*<<< orphan*/  Sectors; int /*<<< orphan*/  Cylinders; int /*<<< orphan*/  BytesPerSector; } ;
struct TYPE_17__ {int Version; int Revision; int Count; TYPE_3__* PartialDescriptors; } ;
struct TYPE_16__ {int /*<<< orphan*/  BytesPerSector; int /*<<< orphan*/  SectorsPerTrack; int /*<<< orphan*/  NumberOfHeads; int /*<<< orphan*/  NumberOfCylinders; } ;
struct TYPE_13__ {int DataSize; } ;
struct TYPE_14__ {TYPE_1__ DeviceSpecificData; } ;
struct TYPE_15__ {TYPE_2__ u; int /*<<< orphan*/  Type; } ;
typedef  TYPE_4__* PVOID ;
typedef  TYPE_5__* PCM_PARTIAL_RESOURCE_LIST ;
typedef  TYPE_4__* PCM_DISK_GEOMETRY_DEVICE_DATA ;
typedef  TYPE_7__ GEOMETRY ;
typedef  int /*<<< orphan*/  CM_PARTIAL_RESOURCE_LIST ;
typedef  int /*<<< orphan*/  CM_DISK_GEOMETRY_DEVICE_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CmResourceTypeDeviceSpecific ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_5__* FrLdrHeapAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrHeapFree (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_HW_RESOURCE_LIST ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XboxDiskGetDriveGeometry (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
PCM_PARTIAL_RESOURCE_LIST
XboxGetHarddiskConfigurationData(UCHAR DriveNumber, ULONG* pSize)
{
    PCM_PARTIAL_RESOURCE_LIST PartialResourceList;
    PCM_DISK_GEOMETRY_DEVICE_DATA DiskGeometry;
    //EXTENDED_GEOMETRY ExtGeometry;
    GEOMETRY Geometry;
    ULONG Size;

    //
    // Initialize returned size
    //
    *pSize = 0;

    /* Set 'Configuration Data' value */
    Size = sizeof(CM_PARTIAL_RESOURCE_LIST) +
           sizeof(CM_DISK_GEOMETRY_DEVICE_DATA);
    PartialResourceList = FrLdrHeapAlloc(Size, TAG_HW_RESOURCE_LIST);
    if (PartialResourceList == NULL)
    {
        ERR("Failed to allocate a full resource descriptor\n");
        return NULL;
    }

    memset(PartialResourceList, 0, Size);
    PartialResourceList->Version = 1;
    PartialResourceList->Revision = 1;
    PartialResourceList->Count = 1;
    PartialResourceList->PartialDescriptors[0].Type =
        CmResourceTypeDeviceSpecific;
//  PartialResourceList->PartialDescriptors[0].ShareDisposition =
//  PartialResourceList->PartialDescriptors[0].Flags =
    PartialResourceList->PartialDescriptors[0].u.DeviceSpecificData.DataSize =
        sizeof(CM_DISK_GEOMETRY_DEVICE_DATA);

    /* Get pointer to geometry data */
    DiskGeometry = (PVOID)(((ULONG_PTR)PartialResourceList) + sizeof(CM_PARTIAL_RESOURCE_LIST));

    /* Get the disk geometry */
    //ExtGeometry.Size = sizeof(EXTENDED_GEOMETRY);

    if (XboxDiskGetDriveGeometry(DriveNumber, &Geometry))
    {
        DiskGeometry->BytesPerSector = Geometry.BytesPerSector;
        DiskGeometry->NumberOfCylinders = Geometry.Cylinders;
        DiskGeometry->SectorsPerTrack = Geometry.Sectors;
        DiskGeometry->NumberOfHeads = Geometry.Heads;
    }
    else
    {
        ERR("Reading disk geometry failed\n");
        FrLdrHeapFree(PartialResourceList, TAG_HW_RESOURCE_LIST);
        return NULL;
    }
    TRACE("Disk %x: %u Cylinders  %u Heads  %u Sectors  %u Bytes\n",
          DriveNumber,
          DiskGeometry->NumberOfCylinders,
          DiskGeometry->NumberOfHeads,
          DiskGeometry->SectorsPerTrack,
          DiskGeometry->BytesPerSector);

    //
    // Return configuration data
    //
    *pSize = Size;
    return PartialResourceList;
}