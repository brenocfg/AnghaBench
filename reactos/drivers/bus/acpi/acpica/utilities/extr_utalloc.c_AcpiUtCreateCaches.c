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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJ_NAMED ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJ_COMMON ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  int /*<<< orphan*/  ACPI_GENERIC_STATE ;
typedef  int /*<<< orphan*/  ACPI_FILE_NODE ;
typedef  int /*<<< orphan*/  ACPI_COMMENT_NODE ;
typedef  int /*<<< orphan*/  ACPI_COMMENT_ADDR_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MAX_COMMENT_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_EXTPARSE_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_NAMESPACE_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_OBJECT_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_PARSE_CACHE_DEPTH ; 
 int /*<<< orphan*/  ACPI_MAX_STATE_CACHE_DEPTH ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGbl_CommentAddrCache ; 
 int /*<<< orphan*/  AcpiGbl_FileCache ; 
 int /*<<< orphan*/  AcpiGbl_GlobalList ; 
 int /*<<< orphan*/  AcpiGbl_NamespaceCache ; 
 int /*<<< orphan*/  AcpiGbl_NsNodeList ; 
 int /*<<< orphan*/  AcpiGbl_OperandCache ; 
 int /*<<< orphan*/  AcpiGbl_PsNodeCache ; 
 int /*<<< orphan*/  AcpiGbl_PsNodeExtCache ; 
 int /*<<< orphan*/  AcpiGbl_RegCommentCache ; 
 int /*<<< orphan*/  AcpiGbl_StateCache ; 
 int /*<<< orphan*/  AcpiOsCreateCache (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtCreateList (char*,int,int /*<<< orphan*/ *) ; 

ACPI_STATUS
AcpiUtCreateCaches (
    void)
{
    ACPI_STATUS             Status;


    /* Object Caches, for frequently used objects */

    Status = AcpiOsCreateCache ("Acpi-Namespace", sizeof (ACPI_NAMESPACE_NODE),
        ACPI_MAX_NAMESPACE_CACHE_DEPTH, &AcpiGbl_NamespaceCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = AcpiOsCreateCache ("Acpi-State", sizeof (ACPI_GENERIC_STATE),
        ACPI_MAX_STATE_CACHE_DEPTH, &AcpiGbl_StateCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = AcpiOsCreateCache ("Acpi-Parse", sizeof (ACPI_PARSE_OBJ_COMMON),
        ACPI_MAX_PARSE_CACHE_DEPTH, &AcpiGbl_PsNodeCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = AcpiOsCreateCache ("Acpi-ParseExt", sizeof (ACPI_PARSE_OBJ_NAMED),
        ACPI_MAX_EXTPARSE_CACHE_DEPTH, &AcpiGbl_PsNodeExtCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = AcpiOsCreateCache ("Acpi-Operand", sizeof (ACPI_OPERAND_OBJECT),
        ACPI_MAX_OBJECT_CACHE_DEPTH, &AcpiGbl_OperandCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

#ifdef ACPI_ASL_COMPILER
    /*
     * For use with the ASL-/ASL+ option. This cache keeps track of regular
     * 0xA9 0x01 comments.
     */
    Status = AcpiOsCreateCache ("Acpi-Comment", sizeof (ACPI_COMMENT_NODE),
        ACPI_MAX_COMMENT_CACHE_DEPTH, &AcpiGbl_RegCommentCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * This cache keeps track of the starting addresses of where the comments
     * lie. This helps prevent duplication of comments.
     */
    Status = AcpiOsCreateCache ("Acpi-Comment-Addr", sizeof (ACPI_COMMENT_ADDR_NODE),
        ACPI_MAX_COMMENT_CACHE_DEPTH, &AcpiGbl_CommentAddrCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /*
     * This cache will be used for nodes that represent files.
     */
    Status = AcpiOsCreateCache ("Acpi-File", sizeof (ACPI_FILE_NODE),
        ACPI_MAX_COMMENT_CACHE_DEPTH, &AcpiGbl_FileCache);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }
#endif


#ifdef ACPI_DBG_TRACK_ALLOCATIONS

    /* Memory allocation lists */

    Status = AcpiUtCreateList ("Acpi-Global", 0,
        &AcpiGbl_GlobalList);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = AcpiUtCreateList ("Acpi-Namespace", sizeof (ACPI_NAMESPACE_NODE),
        &AcpiGbl_NsNodeList);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }
#endif

    return (AE_OK);
}