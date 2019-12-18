#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_26__ {int ReturnBtype; int ReturnFlags; int /*<<< orphan*/  FullPathname; int /*<<< orphan*/  Node; } ;
struct TYPE_23__ {int /*<<< orphan*/  ReferenceCount; } ;
struct TYPE_25__ {TYPE_1__ Common; } ;
struct TYPE_24__ {int /*<<< orphan*/  (* ObjectConverter ) (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__**) ;} ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_SIMPLE_REPAIR_INFO ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_4__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int ACPI_NOT_PACKAGE_ELEMENT ; 
 int ACPI_OBJECT_REPAIRED ; 
 int ACPI_OBJECT_WRAPPED ; 
 int ACPI_RTYPE_BUFFER ; 
 int ACPI_RTYPE_INTEGER ; 
 int ACPI_RTYPE_NONE ; 
 int ACPI_RTYPE_PACKAGE ; 
 int ACPI_RTYPE_STRING ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WARN_ALWAYS ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_NO_RETURN_VALUE ; 
 int /*<<< orphan*/  AE_AML_OPERAND_TYPE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsConvertToBuffer (TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  AcpiNsConvertToInteger (TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  AcpiNsConvertToString (TYPE_3__*,TYPE_3__**) ; 
 TYPE_2__* AcpiNsMatchSimpleRepair (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  AcpiNsRepairNullElement (TYPE_4__*,int,int,TYPE_3__**) ; 
 int /*<<< orphan*/  AcpiNsWrapWithPackage (TYPE_4__*,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_3__*) ; 
 int /*<<< orphan*/  NsSimpleRepair ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__**) ; 

ACPI_STATUS
AcpiNsSimpleRepair (
    ACPI_EVALUATE_INFO      *Info,
    UINT32                  ExpectedBtypes,
    UINT32                  PackageIndex,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_OPERAND_OBJECT     *NewObject = NULL;
    ACPI_STATUS             Status;
    const ACPI_SIMPLE_REPAIR_INFO   *Predefined;


    ACPI_FUNCTION_NAME (NsSimpleRepair);


    /*
     * Special repairs for certain names that are in the repair table.
     * Check if this name is in the list of repairable names.
     */
    Predefined = AcpiNsMatchSimpleRepair (Info->Node,
        Info->ReturnBtype, PackageIndex);
    if (Predefined)
    {
        if (!ReturnObject)
        {
            ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname,
                ACPI_WARN_ALWAYS, "Missing expected return value"));
        }

        Status = Predefined->ObjectConverter (Info->Node, ReturnObject,
            &NewObject);
        if (ACPI_FAILURE (Status))
        {
            /* A fatal error occurred during a conversion */

            ACPI_EXCEPTION ((AE_INFO, Status,
                "During return object analysis"));
            return (Status);
        }
        if (NewObject)
        {
            goto ObjectRepaired;
        }
    }

    /*
     * Do not perform simple object repair unless the return type is not
     * expected.
     */
    if (Info->ReturnBtype & ExpectedBtypes)
    {
        return (AE_OK);
    }

    /*
     * At this point, we know that the type of the returned object was not
     * one of the expected types for this predefined name. Attempt to
     * repair the object by converting it to one of the expected object
     * types for this predefined name.
     */

    /*
     * If there is no return value, check if we require a return value for
     * this predefined name. Either one return value is expected, or none,
     * for both methods and other objects.
     *
     * Try to fix if there was no return object. Warning if failed to fix.
     */
    if (!ReturnObject)
    {
        if (ExpectedBtypes && (!(ExpectedBtypes & ACPI_RTYPE_NONE)))
        {
            if (PackageIndex != ACPI_NOT_PACKAGE_ELEMENT)
            {
                ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname,
                    ACPI_WARN_ALWAYS, "Found unexpected NULL package element"));

                Status = AcpiNsRepairNullElement (Info, ExpectedBtypes,
                    PackageIndex, ReturnObjectPtr);
                if (ACPI_SUCCESS (Status))
                {
                    return (AE_OK); /* Repair was successful */
                }
            }
            else
            {
                ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname,
                    ACPI_WARN_ALWAYS, "Missing expected return value"));
            }

            return (AE_AML_NO_RETURN_VALUE);
        }
    }

    if (ExpectedBtypes & ACPI_RTYPE_INTEGER)
    {
        Status = AcpiNsConvertToInteger (ReturnObject, &NewObject);
        if (ACPI_SUCCESS (Status))
        {
            goto ObjectRepaired;
        }
    }
    if (ExpectedBtypes & ACPI_RTYPE_STRING)
    {
        Status = AcpiNsConvertToString (ReturnObject, &NewObject);
        if (ACPI_SUCCESS (Status))
        {
            goto ObjectRepaired;
        }
    }
    if (ExpectedBtypes & ACPI_RTYPE_BUFFER)
    {
        Status = AcpiNsConvertToBuffer (ReturnObject, &NewObject);
        if (ACPI_SUCCESS (Status))
        {
            goto ObjectRepaired;
        }
    }
    if (ExpectedBtypes & ACPI_RTYPE_PACKAGE)
    {
        /*
         * A package is expected. We will wrap the existing object with a
         * new package object. It is often the case that if a variable-length
         * package is required, but there is only a single object needed, the
         * BIOS will return that object instead of wrapping it with a Package
         * object. Note: after the wrapping, the package will be validated
         * for correct contents (expected object type or types).
         */
        Status = AcpiNsWrapWithPackage (Info, ReturnObject, &NewObject);
        if (ACPI_SUCCESS (Status))
        {
            /*
             * The original object just had its reference count
             * incremented for being inserted into the new package.
             */
            *ReturnObjectPtr = NewObject;       /* New Package object */
            Info->ReturnFlags |= ACPI_OBJECT_REPAIRED;
            return (AE_OK);
        }
    }

    /* We cannot repair this object */

    return (AE_AML_OPERAND_TYPE);


ObjectRepaired:

    /* Object was successfully repaired */

    if (PackageIndex != ACPI_NOT_PACKAGE_ELEMENT)
    {
        /* Update reference count of new object */

        if (!(Info->ReturnFlags & ACPI_OBJECT_WRAPPED))
        {
            NewObject->Common.ReferenceCount =
                ReturnObject->Common.ReferenceCount;
        }

        ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
            "%s: Converted %s to expected %s at Package index %u\n",
            Info->FullPathname, AcpiUtGetObjectTypeName (ReturnObject),
            AcpiUtGetObjectTypeName (NewObject), PackageIndex));
    }
    else
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
            "%s: Converted %s to expected %s\n",
            Info->FullPathname, AcpiUtGetObjectTypeName (ReturnObject),
            AcpiUtGetObjectTypeName (NewObject)));
    }

    /* Delete old object, install the new return object */

    AcpiUtRemoveReference (ReturnObject);
    *ReturnObjectPtr = NewObject;
    Info->ReturnFlags |= ACPI_OBJECT_REPAIRED;
    return (AE_OK);
}