#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ Node; } ;
struct TYPE_5__ {TYPE_1__ Scope; } ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AcpiNsExternalizeName (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char**) ; 
 char* AcpiNsGetNormalizedPathname (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiNsNormalizePathname (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

char *
AcpiNsBuildPrefixedPathname (
    ACPI_GENERIC_STATE      *PrefixScope,
    const char              *InternalPath)
{
    ACPI_STATUS             Status;
    char                    *FullPath = NULL;
    char                    *ExternalPath = NULL;
    char                    *PrefixPath = NULL;
    SIZE_T                  PrefixPathLength = 0;


    /* If there is a prefix, get the pathname to it */

    if (PrefixScope && PrefixScope->Scope.Node)
    {
        PrefixPath = AcpiNsGetNormalizedPathname (PrefixScope->Scope.Node, TRUE);
        if (PrefixPath)
        {
            PrefixPathLength = strlen (PrefixPath);
        }
    }

    Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, InternalPath,
        NULL, &ExternalPath);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    /* Merge the prefix path and the path. 2 is for one dot and trailing null */

    FullPath = ACPI_ALLOCATE_ZEROED (
        PrefixPathLength + strlen (ExternalPath) + 2);
    if (!FullPath)
    {
        goto Cleanup;
    }

    /* Don't merge if the External path is already fully qualified */

    if (PrefixPath &&
        (*ExternalPath != '\\') &&
        (*ExternalPath != '^'))
    {
        strcat (FullPath, PrefixPath);
        if (PrefixPath[1])
        {
            strcat (FullPath, ".");
        }
    }

    AcpiNsNormalizePathname (ExternalPath);
    strcat (FullPath, ExternalPath);

Cleanup:
    if (PrefixPath)
    {
        ACPI_FREE (PrefixPath);
    }
    if (ExternalPath)
    {
        ACPI_FREE (ExternalPath);
    }

    return (FullPath);
}