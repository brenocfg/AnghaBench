#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ ACPI_SIZE ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 char* ACPI_ALLOCATE_ZEROED (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_DB_NAMES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_GET_FUNCTION_NAME ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AcpiNsBuildNormalizedPath (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NsGetNormalizedPathname ; 
 int /*<<< orphan*/  return_PTR (char*) ; 

char *
AcpiNsGetNormalizedPathname (
    ACPI_NAMESPACE_NODE     *Node,
    BOOLEAN                 NoTrailing)
{
    char                    *NameBuffer;
    ACPI_SIZE               Size;


    ACPI_FUNCTION_TRACE_PTR (NsGetNormalizedPathname, Node);


    /* Calculate required buffer size based on depth below root */

    Size = AcpiNsBuildNormalizedPath (Node, NULL, 0, NoTrailing);
    if (!Size)
    {
        return_PTR (NULL);
    }

    /* Allocate a buffer to be returned to caller */

    NameBuffer = ACPI_ALLOCATE_ZEROED (Size);
    if (!NameBuffer)
    {
        ACPI_ERROR ((AE_INFO,
            "Could not allocate %u bytes", (UINT32) Size));
        return_PTR (NULL);
    }

    /* Build the path in the allocated buffer */

    (void) AcpiNsBuildNormalizedPath (Node, NameBuffer, Size, NoTrailing);

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_NAMES, "%s: Path \"%s\"\n",
        ACPI_GET_FUNCTION_NAME, NameBuffer));

    return_PTR (NameBuffer);
}