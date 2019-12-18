#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_5__ {struct TYPE_5__* Parent; int /*<<< orphan*/  Name; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_MOVE_32_TO_32 (char*,int /*<<< orphan*/ *) ; 
 int ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_PATH_PUT8 (char*,int,char,int) ; 
 char AML_DUAL_NAME_PREFIX ; 
 char AML_ROOT_PREFIX ; 
 TYPE_1__* AcpiGbl_RootNode ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NsBuildNormalizedPath ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

UINT32
AcpiNsBuildNormalizedPath (
    ACPI_NAMESPACE_NODE     *Node,
    char                    *FullPath,
    UINT32                  PathSize,
    BOOLEAN                 NoTrailing)
{
    UINT32                  Length = 0, i;
    char                    Name[ACPI_NAMESEG_SIZE];
    BOOLEAN                 DoNoTrailing;
    char                    c, *Left, *Right;
    ACPI_NAMESPACE_NODE     *NextNode;


    ACPI_FUNCTION_TRACE_PTR (NsBuildNormalizedPath, Node);


#define ACPI_PATH_PUT8(Path, Size, Byte, Length)    \
    do {                                            \
        if ((Length) < (Size))                      \
        {                                           \
            (Path)[(Length)] = (Byte);              \
        }                                           \
        (Length)++;                                 \
    } while (0)

    /*
     * Make sure the PathSize is correct, so that we don't need to
     * validate both FullPath and PathSize.
     */
    if (!FullPath)
    {
        PathSize = 0;
    }

    if (!Node)
    {
        goto BuildTrailingNull;
    }

    NextNode = Node;
    while (NextNode && NextNode != AcpiGbl_RootNode)
    {
        if (NextNode != Node)
        {
            ACPI_PATH_PUT8(FullPath, PathSize, AML_DUAL_NAME_PREFIX, Length);
        }

        ACPI_MOVE_32_TO_32 (Name, &NextNode->Name);
        DoNoTrailing = NoTrailing;
        for (i = 0; i < 4; i++)
        {
            c = Name[4-i-1];
            if (DoNoTrailing && c != '_')
            {
                DoNoTrailing = FALSE;
            }
            if (!DoNoTrailing)
            {
                ACPI_PATH_PUT8(FullPath, PathSize, c, Length);
            }
        }

        NextNode = NextNode->Parent;
    }

    ACPI_PATH_PUT8(FullPath, PathSize, AML_ROOT_PREFIX, Length);

    /* Reverse the path string */

    if (Length <= PathSize)
    {
        Left = FullPath;
        Right = FullPath+Length - 1;

        while (Left < Right)
        {
            c = *Left;
            *Left++ = *Right;
            *Right-- = c;
        }
    }

    /* Append the trailing null */

BuildTrailingNull:
    ACPI_PATH_PUT8 (FullPath, PathSize, '\0', Length);

#undef ACPI_PATH_PUT8

    return_UINT32 (Length);
}