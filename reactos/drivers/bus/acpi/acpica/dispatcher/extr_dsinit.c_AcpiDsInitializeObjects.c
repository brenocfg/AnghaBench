#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/  OpRegionCount; int /*<<< orphan*/  MethodCount; int /*<<< orphan*/  SerializedMethodCount; int /*<<< orphan*/  NonSerialMethodCount; int /*<<< orphan*/  SerialMethodCount; int /*<<< orphan*/  DeviceCount; int /*<<< orphan*/  ObjectCount; int /*<<< orphan*/  TableIndex; int /*<<< orphan*/  OwnerId; } ;
struct TYPE_6__ {int /*<<< orphan*/  OemTableId; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OWNER_ID ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_2__ ACPI_INIT_WALK_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NS_WALK_NO_UNLOCK ; 
 int /*<<< orphan*/  ACPI_SIG_DSDT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDsInitOneObject ; 
 int /*<<< orphan*/  AcpiGetTableByIndex (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  AcpiNsWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbGetOwnerId (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsInitializeObjects ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsInitializeObjects (
    UINT32                  TableIndex,
    ACPI_NAMESPACE_NODE     *StartNode)
{
    ACPI_STATUS             Status;
    ACPI_INIT_WALK_INFO     Info;
    ACPI_TABLE_HEADER       *Table;
    ACPI_OWNER_ID           OwnerId;


    ACPI_FUNCTION_TRACE (DsInitializeObjects);


    Status = AcpiTbGetOwnerId (TableIndex, &OwnerId);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
        "**** Starting initialization of namespace objects ****\n"));

    /* Set all init info to zero */

    memset (&Info, 0, sizeof (ACPI_INIT_WALK_INFO));

    Info.OwnerId = OwnerId;
    Info.TableIndex = TableIndex;

    /* Walk entire namespace from the supplied root */

    /*
     * We don't use AcpiWalkNamespace since we do not want to acquire
     * the namespace reader lock.
     */
    Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, StartNode, ACPI_UINT32_MAX,
        ACPI_NS_WALK_NO_UNLOCK, AcpiDsInitOneObject, NULL, &Info, NULL);
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status, "During WalkNamespace"));
    }

    Status = AcpiGetTableByIndex (TableIndex, &Table);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* DSDT is always the first AML table */

    if (ACPI_COMPARE_NAMESEG (Table->Signature, ACPI_SIG_DSDT))
    {
        ACPI_DEBUG_PRINT_RAW ((ACPI_DB_INIT,
            "\nACPI table initialization:\n"));
    }

    /* Summary of objects initialized */

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_INIT,
        "Table [%4.4s: %-8.8s] (id %.2X) - %4u Objects with %3u Devices, "
        "%3u Regions, %4u Methods (%u/%u/%u Serial/Non/Cvt)\n",
        Table->Signature, Table->OemTableId, OwnerId, Info.ObjectCount,
        Info.DeviceCount,Info.OpRegionCount, Info.MethodCount,
        Info.SerialMethodCount, Info.NonSerialMethodCount,
        Info.SerializedMethodCount));

    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH, "%u Methods, %u Regions\n",
        Info.MethodCount, Info.OpRegionCount));

    return_ACPI_STATUS (AE_OK);
}