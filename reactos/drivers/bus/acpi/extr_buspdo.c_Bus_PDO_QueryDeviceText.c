#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_11__ {int DeviceTextType; } ;
struct TYPE_12__ {TYPE_1__ QueryDeviceText; } ;
struct TYPE_16__ {TYPE_2__ Parameters; } ;
struct TYPE_13__ {int /*<<< orphan*/  Information; int /*<<< orphan*/  Status; } ;
struct TYPE_15__ {TYPE_3__ IoStatus; } ;
struct TYPE_14__ {int /*<<< orphan*/  AcpiHandle; int /*<<< orphan*/  HardwareIDs; } ;
typedef  char* PWCHAR ;
typedef  TYPE_4__* PPDO_DEVICE_DATA ;
typedef  TYPE_5__* PIRP ;
typedef  TYPE_6__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
#define  DeviceTextDescription 128 
 char* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 TYPE_6__* IoGetCurrentIrpStackLocation (TYPE_5__*) ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  PagedPool ; 
 char* ProcessorNameString ; 
 int /*<<< orphan*/  RtlCopyMemory (char*,char*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  wcslen (char*) ; 
 int /*<<< orphan*/  wcsstr (int /*<<< orphan*/ ,char*) ; 

NTSTATUS
Bus_PDO_QueryDeviceText(
     PPDO_DEVICE_DATA     DeviceData,
      PIRP   Irp )
{
    PWCHAR  Buffer, Temp;
    PIO_STACK_LOCATION   stack;
    NTSTATUS    status = Irp->IoStatus.Status;
    PAGED_CODE ();

    stack = IoGetCurrentIrpStackLocation (Irp);

    switch (stack->Parameters.QueryDeviceText.DeviceTextType) {

    case DeviceTextDescription:

        if (!Irp->IoStatus.Information) {
            if (wcsstr (DeviceData->HardwareIDs, L"PNP000") != 0)
                Temp = L"Programmable interrupt controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP010") != 0)
                Temp = L"System timer";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP020") != 0)
                Temp = L"DMA controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP03") != 0)
                Temp = L"Keyboard";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP040") != 0)
                Temp = L"Parallel port";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP05") != 0)
                Temp = L"Serial port";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP06") != 0)
                Temp = L"Disk controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP07") != 0)
                Temp = L"Disk controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP09") != 0)
                Temp = L"Display adapter";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0A0") != 0)
                Temp = L"Bus controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0E0") != 0)
                Temp = L"PCMCIA controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0F") != 0)
                Temp = L"Mouse device";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP8") != 0)
                Temp = L"Network adapter";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNPA0") != 0)
                Temp = L"SCSI controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNPB0") != 0)
                Temp = L"Multimedia device";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNPC00") != 0)
                Temp = L"Modem";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0C0C") != 0)
                Temp = L"Power Button";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0C0E") != 0)
                Temp = L"Sleep Button";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0C0D") != 0)
                Temp = L"Lid Switch";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0C09") != 0)
                Temp = L"ACPI Embedded Controller";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0C0B") != 0)
                Temp = L"ACPI Fan";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0A03") != 0 ||
                     wcsstr(DeviceData->HardwareIDs, L"PNP0A08") != 0)
                Temp = L"PCI Root Bridge";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0C0A") != 0)
                Temp = L"ACPI Battery";
            else if (wcsstr(DeviceData->HardwareIDs, L"PNP0C0F") != 0)
                Temp = L"PCI Interrupt Link";
            else if (wcsstr(DeviceData->HardwareIDs, L"ACPI_PWR") != 0)
                Temp = L"ACPI Power Resource";
            else if (wcsstr(DeviceData->HardwareIDs, L"Processor") != 0)
            {
                if (ProcessorNameString != NULL)
                    Temp = ProcessorNameString;
                else
                    Temp = L"Processor";
            }
            else if (wcsstr(DeviceData->HardwareIDs, L"ThermalZone") != 0)
                Temp = L"ACPI Thermal Zone";
            else if (wcsstr(DeviceData->HardwareIDs, L"ACPI0002") != 0)
                Temp = L"Smart Battery";
            else if (wcsstr(DeviceData->HardwareIDs, L"ACPI0003") != 0)
                Temp = L"AC Adapter";
            /* Simply checking if AcpiHandle is NULL eliminates the need to check
             * for the 4 different names that ACPI knows the fixed feature button as internally
             */
            else if (!DeviceData->AcpiHandle)
                Temp = L"ACPI Fixed Feature Button";
            else
                Temp = L"Other ACPI device";

            Buffer = ExAllocatePoolWithTag(PagedPool, (wcslen(Temp) + 1) * sizeof(WCHAR), 'IpcA');

            if (!Buffer) {
                status = STATUS_INSUFFICIENT_RESOURCES;
                break;
            }

            RtlCopyMemory (Buffer, Temp, (wcslen(Temp) + 1) * sizeof(WCHAR));

            DPRINT("\tDeviceTextDescription :%ws\n", Buffer);

            Irp->IoStatus.Information = (ULONG_PTR) Buffer;
            status = STATUS_SUCCESS;
        }
        break;

    default:
        break;
    }

    return status;

}