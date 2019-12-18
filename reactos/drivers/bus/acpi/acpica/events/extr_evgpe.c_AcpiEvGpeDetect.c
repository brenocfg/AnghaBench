#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_7__ {size_t RegisterCount; struct TYPE_7__* Next; int /*<<< orphan*/ * EventInfo; TYPE_2__* RegisterInfo; int /*<<< orphan*/ * Node; } ;
struct TYPE_6__ {int EnableForRun; int EnableForWake; int BaseGpeNumber; } ;
struct TYPE_5__ {TYPE_3__* GpeBlockListHead; } ;
typedef  int ACPI_SIZE ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_1__ ACPI_GPE_XRUPT_INFO ;
typedef  TYPE_2__ ACPI_GPE_REGISTER_INFO ;
typedef  int /*<<< orphan*/  ACPI_GPE_EVENT_INFO ;
typedef  TYPE_3__ ACPI_GPE_BLOCK_INFO ;
typedef  int /*<<< orphan*/  ACPI_CPU_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INTERRUPTS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_REGISTER_WIDTH ; 
 size_t ACPI_INTERRUPT_NOT_HANDLED ; 
 size_t AcpiEvDetectGpe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  AcpiGbl_GpeLock ; 
 int /*<<< orphan*/  AcpiOsAcquireLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvGpeDetect ; 

UINT32
AcpiEvGpeDetect (
    ACPI_GPE_XRUPT_INFO     *GpeXruptList)
{
    ACPI_GPE_BLOCK_INFO     *GpeBlock;
    ACPI_NAMESPACE_NODE     *GpeDevice;
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;
    ACPI_GPE_EVENT_INFO     *GpeEventInfo;
    UINT32                  GpeNumber;
    UINT32                  IntStatus = ACPI_INTERRUPT_NOT_HANDLED;
    ACPI_CPU_FLAGS          Flags;
    UINT32                  i;
    UINT32                  j;


    ACPI_FUNCTION_NAME (EvGpeDetect);

    /* Check for the case where there are no GPEs */

    if (!GpeXruptList)
    {
        return (IntStatus);
    }

    /*
     * We need to obtain the GPE lock for both the data structs and registers
     * Note: Not necessary to obtain the hardware lock, since the GPE
     * registers are owned by the GpeLock.
     */
    Flags = AcpiOsAcquireLock (AcpiGbl_GpeLock);

    /* Examine all GPE blocks attached to this interrupt level */

    GpeBlock = GpeXruptList->GpeBlockListHead;
    while (GpeBlock)
    {
        GpeDevice = GpeBlock->Node;

        /*
         * Read all of the 8-bit GPE status and enable registers in this GPE
         * block, saving all of them. Find all currently active GP events.
         */
        for (i = 0; i < GpeBlock->RegisterCount; i++)
        {
            /* Get the next status/enable pair */

            GpeRegisterInfo = &GpeBlock->RegisterInfo[i];

            /*
             * Optimization: If there are no GPEs enabled within this
             * register, we can safely ignore the entire register.
             */
            if (!(GpeRegisterInfo->EnableForRun |
                  GpeRegisterInfo->EnableForWake))
            {
                ACPI_DEBUG_PRINT ((ACPI_DB_INTERRUPTS,
                    "Ignore disabled registers for GPE %02X-%02X: "
                    "RunEnable=%02X, WakeEnable=%02X\n",
                    GpeRegisterInfo->BaseGpeNumber,
                    GpeRegisterInfo->BaseGpeNumber + (ACPI_GPE_REGISTER_WIDTH - 1),
                    GpeRegisterInfo->EnableForRun,
                    GpeRegisterInfo->EnableForWake));
                continue;
            }

            /* Now look at the individual GPEs in this byte register */

            for (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++)
            {
                /* Detect and dispatch one GPE bit */

                GpeEventInfo = &GpeBlock->EventInfo[((ACPI_SIZE) i *
                    ACPI_GPE_REGISTER_WIDTH) + j];
                GpeNumber = j + GpeRegisterInfo->BaseGpeNumber;
                AcpiOsReleaseLock (AcpiGbl_GpeLock, Flags);
                IntStatus |= AcpiEvDetectGpe (
                    GpeDevice, GpeEventInfo, GpeNumber);
                Flags = AcpiOsAcquireLock (AcpiGbl_GpeLock);
            }
        }

        GpeBlock = GpeBlock->Next;
    }

    AcpiOsReleaseLock (AcpiGbl_GpeLock, Flags);
    return (IntStatus);
}