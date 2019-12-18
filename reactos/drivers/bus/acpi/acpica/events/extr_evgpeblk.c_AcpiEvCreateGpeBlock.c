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
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT32 ;
typedef  void* UINT16 ;
struct TYPE_18__ {int SciInterrupt; } ;
struct TYPE_17__ {int GpeCount; int RegisterCount; int BlockBaseNumber; struct TYPE_17__* EventInfo; struct TYPE_17__* RegisterInfo; void* Initialized; TYPE_2__* Node; int /*<<< orphan*/  SpaceId; int /*<<< orphan*/  Address; } ;
struct TYPE_16__ {void* ExecuteByOwnerId; TYPE_2__* GpeDevice; TYPE_4__* GpeBlock; } ;
struct TYPE_14__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_15__ {TYPE_1__ Name; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_NAMESPACE_NODE ;
typedef  TYPE_3__ ACPI_GPE_WALK_INFO ;
typedef  TYPE_4__ ACPI_GPE_BLOCK_INFO ;

/* Variables and functions */
 TYPE_4__* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_REGISTER_WIDTH ; 
 int /*<<< orphan*/  ACPI_NS_WALK_NO_UNLOCK ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AcpiCurrentGpeCount ; 
 int /*<<< orphan*/  AcpiEvCreateGpeInfoBlocks (TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiEvInstallGpeBlock (TYPE_4__*,int) ; 
 int /*<<< orphan*/  AcpiEvMatchGpeMethod ; 
 void* AcpiGbl_AllGpesInitialized ; 
 TYPE_7__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiNsWalkNamespace (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EvCreateGpeBlock ; 
 void* FALSE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvCreateGpeBlock (
    ACPI_NAMESPACE_NODE     *GpeDevice,
    UINT64                  Address,
    UINT8                   SpaceId,
    UINT32                  RegisterCount,
    UINT16                  GpeBlockBaseNumber,
    UINT32                  InterruptNumber,
    ACPI_GPE_BLOCK_INFO     **ReturnGpeBlock)
{
    ACPI_STATUS             Status;
    ACPI_GPE_BLOCK_INFO     *GpeBlock;
    ACPI_GPE_WALK_INFO      WalkInfo;


    ACPI_FUNCTION_TRACE (EvCreateGpeBlock);


    if (!RegisterCount)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Allocate a new GPE block */

    GpeBlock = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_GPE_BLOCK_INFO));
    if (!GpeBlock)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Initialize the new GPE block */

    GpeBlock->Address = Address;
    GpeBlock->SpaceId = SpaceId;
    GpeBlock->Node = GpeDevice;
    GpeBlock->GpeCount = (UINT16) (RegisterCount * ACPI_GPE_REGISTER_WIDTH);
    GpeBlock->Initialized = FALSE;
    GpeBlock->RegisterCount = RegisterCount;
    GpeBlock->BlockBaseNumber = GpeBlockBaseNumber;

    /*
     * Create the RegisterInfo and EventInfo sub-structures
     * Note: disables and clears all GPEs in the block
     */
    Status = AcpiEvCreateGpeInfoBlocks (GpeBlock);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (GpeBlock);
        return_ACPI_STATUS (Status);
    }

    /* Install the new block in the global lists */

    Status = AcpiEvInstallGpeBlock (GpeBlock, InterruptNumber);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (GpeBlock->RegisterInfo);
        ACPI_FREE (GpeBlock->EventInfo);
        ACPI_FREE (GpeBlock);
        return_ACPI_STATUS (Status);
    }

    AcpiGbl_AllGpesInitialized = FALSE;

    /* Find all GPE methods (_Lxx or_Exx) for this block */

    WalkInfo.GpeBlock = GpeBlock;
    WalkInfo.GpeDevice = GpeDevice;
    WalkInfo.ExecuteByOwnerId = FALSE;

    (void) AcpiNsWalkNamespace (ACPI_TYPE_METHOD, GpeDevice,
        ACPI_UINT32_MAX, ACPI_NS_WALK_NO_UNLOCK,
        AcpiEvMatchGpeMethod, NULL, &WalkInfo, NULL);

    /* Return the new block */

    if (ReturnGpeBlock)
    {
        (*ReturnGpeBlock) = GpeBlock;
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_INIT,
        "    Initialized GPE %02X to %02X [%4.4s] %u regs on interrupt 0x%X%s\n",
        (UINT32) GpeBlock->BlockBaseNumber,
        (UINT32) (GpeBlock->BlockBaseNumber + (GpeBlock->GpeCount - 1)),
        GpeDevice->Name.Ascii, GpeBlock->RegisterCount, InterruptNumber,
        InterruptNumber == AcpiGbl_FADT.SciInterrupt ? " (SCI)" : ""));

    /* Update global count of currently available GPEs */

    AcpiCurrentGpeCount += GpeBlock->GpeCount;
    return_ACPI_STATUS (AE_OK);
}