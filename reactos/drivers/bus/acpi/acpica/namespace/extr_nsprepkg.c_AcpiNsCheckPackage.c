#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_34__ {int /*<<< orphan*/  NodeFlags; int /*<<< orphan*/  FullPathname; TYPE_7__* Predefined; } ;
struct TYPE_30__ {int Length; } ;
struct TYPE_29__ {size_t Count; TYPE_8__** Elements; } ;
struct TYPE_28__ {int /*<<< orphan*/  Type; } ;
struct TYPE_27__ {int /*<<< orphan*/  Value; } ;
struct TYPE_33__ {TYPE_5__ Buffer; TYPE_4__ Package; TYPE_3__ Common; TYPE_2__ Integer; } ;
struct TYPE_31__ {int Type; size_t Count1; size_t Count2; int /*<<< orphan*/  ObjectType2; int /*<<< orphan*/  ObjectType1; } ;
struct TYPE_26__ {size_t Count; int /*<<< orphan*/  TailObjectType; int /*<<< orphan*/ * ObjectType; } ;
struct TYPE_32__ {TYPE_6__ RetInfo; TYPE_1__ RetInfo3; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_7__ ACPI_PREDEFINED_INFO ;
typedef  TYPE_8__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_9__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_NAMES ; 
 int /*<<< orphan*/  ACPI_DB_REPAIR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
#define  ACPI_PTYPE1_FIXED 140 
#define  ACPI_PTYPE1_OPTION 139 
#define  ACPI_PTYPE1_VAR 138 
#define  ACPI_PTYPE2 137 
#define  ACPI_PTYPE2_COUNT 136 
#define  ACPI_PTYPE2_FIXED 135 
#define  ACPI_PTYPE2_FIX_VAR 134 
#define  ACPI_PTYPE2_MIN 133 
#define  ACPI_PTYPE2_PKG_COUNT 132 
#define  ACPI_PTYPE2_REV_FIXED 131 
#define  ACPI_PTYPE2_UUID_PAIR 130 
#define  ACPI_PTYPE2_VAR_VAR 129 
#define  ACPI_PTYPE_CUSTOM 128 
 int /*<<< orphan*/  ACPI_RTYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_AML_INTERNAL ; 
 int /*<<< orphan*/  AE_AML_OPERAND_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsCheckObjectType (TYPE_9__*,TYPE_8__**,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  AcpiNsCheckPackageElements (TYPE_9__*,TYPE_8__**,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiNsCheckPackageList (TYPE_9__*,TYPE_7__ const*,TYPE_8__**,size_t) ; 
 int /*<<< orphan*/  AcpiNsCustomPackage (TYPE_9__*,TYPE_8__**,size_t) ; 
 int /*<<< orphan*/  AcpiNsRemoveNullElements (TYPE_9__*,int,TYPE_8__*) ; 
 int /*<<< orphan*/  AcpiNsWrapWithPackage (TYPE_9__*,TYPE_8__*,TYPE_8__**) ; 
 int /*<<< orphan*/  NsCheckPackage ; 

ACPI_STATUS
AcpiNsCheckPackage (
    ACPI_EVALUATE_INFO          *Info,
    ACPI_OPERAND_OBJECT         **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT         *ReturnObject = *ReturnObjectPtr;
    const ACPI_PREDEFINED_INFO  *Package;
    ACPI_OPERAND_OBJECT         **Elements;
    ACPI_STATUS                 Status = AE_OK;
    UINT32                      ExpectedCount;
    UINT32                      Count;
    UINT32                      i;


    ACPI_FUNCTION_NAME (NsCheckPackage);


    /* The package info for this name is in the next table entry */

    Package = Info->Predefined + 1;

    ACPI_DEBUG_PRINT ((ACPI_DB_NAMES,
        "%s Validating return Package of Type %X, Count %X\n",
        Info->FullPathname, Package->RetInfo.Type,
        ReturnObject->Package.Count));

    /*
     * For variable-length Packages, we can safely remove all embedded
     * and trailing NULL package elements
     */
    AcpiNsRemoveNullElements (Info, Package->RetInfo.Type, ReturnObject);

    /* Extract package count and elements array */

    Elements = ReturnObject->Package.Elements;
    Count = ReturnObject->Package.Count;

    /*
     * Most packages must have at least one element. The only exception
     * is the variable-length package (ACPI_PTYPE1_VAR).
     */
    if (!Count)
    {
        if (Package->RetInfo.Type == ACPI_PTYPE1_VAR)
        {
            return (AE_OK);
        }

        ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname, Info->NodeFlags,
            "Return Package has no elements (empty)"));

        return (AE_AML_OPERAND_VALUE);
    }

    /*
     * Decode the type of the expected package contents
     *
     * PTYPE1 packages contain no subpackages
     * PTYPE2 packages contain subpackages
     */
    switch (Package->RetInfo.Type)
    {
    case ACPI_PTYPE_CUSTOM:

        Status = AcpiNsCustomPackage (Info, Elements, Count);
        break;

    case ACPI_PTYPE1_FIXED:
        /*
         * The package count is fixed and there are no subpackages
         *
         * If package is too small, exit.
         * If package is larger than expected, issue warning but continue
         */
        ExpectedCount = Package->RetInfo.Count1 + Package->RetInfo.Count2;
        if (Count < ExpectedCount)
        {
            goto PackageTooSmall;
        }
        else if (Count > ExpectedCount)
        {
            ACPI_DEBUG_PRINT ((ACPI_DB_REPAIR,
                "%s: Return Package is larger than needed - "
                "found %u, expected %u\n",
                Info->FullPathname, Count, ExpectedCount));
        }

        /* Validate all elements of the returned package */

        Status = AcpiNsCheckPackageElements (Info, Elements,
            Package->RetInfo.ObjectType1, Package->RetInfo.Count1,
            Package->RetInfo.ObjectType2, Package->RetInfo.Count2, 0);
        break;

    case ACPI_PTYPE1_VAR:
        /*
         * The package count is variable, there are no subpackages, and all
         * elements must be of the same type
         */
        for (i = 0; i < Count; i++)
        {
            Status = AcpiNsCheckObjectType (Info, Elements,
                Package->RetInfo.ObjectType1, i);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            Elements++;
        }
        break;

    case ACPI_PTYPE1_OPTION:
        /*
         * The package count is variable, there are no subpackages. There are
         * a fixed number of required elements, and a variable number of
         * optional elements.
         *
         * Check if package is at least as large as the minimum required
         */
        ExpectedCount = Package->RetInfo3.Count;
        if (Count < ExpectedCount)
        {
            goto PackageTooSmall;
        }

        /* Variable number of sub-objects */

        for (i = 0; i < Count; i++)
        {
            if (i < Package->RetInfo3.Count)
            {
                /* These are the required package elements (0, 1, or 2) */

                Status = AcpiNsCheckObjectType (Info, Elements,
                    Package->RetInfo3.ObjectType[i], i);
                if (ACPI_FAILURE (Status))
                {
                    return (Status);
                }
            }
            else
            {
                /* These are the optional package elements */

                Status = AcpiNsCheckObjectType (Info, Elements,
                    Package->RetInfo3.TailObjectType, i);
                if (ACPI_FAILURE (Status))
                {
                    return (Status);
                }
            }

            Elements++;
        }
        break;

    case ACPI_PTYPE2_REV_FIXED:

        /* First element is the (Integer) revision */

        Status = AcpiNsCheckObjectType (
            Info, Elements, ACPI_RTYPE_INTEGER, 0);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        Elements++;
        Count--;

        /* Examine the subpackages */

        Status = AcpiNsCheckPackageList (Info, Package, Elements, Count);
        break;

    case ACPI_PTYPE2_PKG_COUNT:

        /* First element is the (Integer) count of subpackages to follow */

        Status = AcpiNsCheckObjectType (
            Info, Elements, ACPI_RTYPE_INTEGER, 0);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        /*
         * Count cannot be larger than the parent package length, but allow it
         * to be smaller. The >= accounts for the Integer above.
         */
        ExpectedCount = (UINT32) (*Elements)->Integer.Value;
        if (ExpectedCount >= Count)
        {
            goto PackageTooSmall;
        }

        Count = ExpectedCount;
        Elements++;

        /* Examine the subpackages */

        Status = AcpiNsCheckPackageList (Info, Package, Elements, Count);
        break;

    case ACPI_PTYPE2:
    case ACPI_PTYPE2_FIXED:
    case ACPI_PTYPE2_MIN:
    case ACPI_PTYPE2_COUNT:
    case ACPI_PTYPE2_FIX_VAR:
        /*
         * These types all return a single Package that consists of a
         * variable number of subpackages.
         *
         * First, ensure that the first element is a subpackage. If not,
         * the BIOS may have incorrectly returned the object as a single
         * package instead of a Package of Packages (a common error if
         * there is only one entry). We may be able to repair this by
         * wrapping the returned Package with a new outer Package.
         */
        if (*Elements && ((*Elements)->Common.Type != ACPI_TYPE_PACKAGE))
        {
            /* Create the new outer package and populate it */

            Status = AcpiNsWrapWithPackage (
                Info, ReturnObject, ReturnObjectPtr);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }

            /* Update locals to point to the new package (of 1 element) */

            ReturnObject = *ReturnObjectPtr;
            Elements = ReturnObject->Package.Elements;
            Count = 1;
        }

        /* Examine the subpackages */

        Status = AcpiNsCheckPackageList (Info, Package, Elements, Count);
        break;

    case ACPI_PTYPE2_VAR_VAR:
        /*
         * Returns a variable list of packages, each with a variable list
         * of objects.
         */
        break;

    case ACPI_PTYPE2_UUID_PAIR:

        /* The package must contain pairs of (UUID + type) */

        if (Count & 1)
        {
            ExpectedCount = Count + 1;
            goto PackageTooSmall;
        }

        while (Count > 0)
        {
            Status = AcpiNsCheckObjectType(Info, Elements,
                Package->RetInfo.ObjectType1, 0);
            if (ACPI_FAILURE(Status))
            {
                return (Status);
            }

            /* Validate length of the UUID buffer */

            if ((*Elements)->Buffer.Length != 16)
            {
                ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname,
                    Info->NodeFlags, "Invalid length for UUID Buffer"));
                return (AE_AML_OPERAND_VALUE);
            }

            Status = AcpiNsCheckObjectType(Info, Elements + 1,
                Package->RetInfo.ObjectType2, 0);
            if (ACPI_FAILURE(Status))
            {
                return (Status);
            }

            Elements += 2;
            Count -= 2;
        }
        break;

    default:

        /* Should not get here if predefined info table is correct */

        ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname, Info->NodeFlags,
            "Invalid internal return type in table entry: %X",
            Package->RetInfo.Type));

        return (AE_AML_INTERNAL);
    }

    return (Status);


PackageTooSmall:

    /* Error exit for the case with an incorrect package count */

    ACPI_WARN_PREDEFINED ((AE_INFO, Info->FullPathname, Info->NodeFlags,
        "Return Package is too small - found %u elements, expected %u",
        Count, ExpectedCount));

    return (AE_AML_OPERAND_VALUE);
}