#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* CurrAttr; } ;
struct TYPE_7__ {scalar_t__ Type; } ;
typedef  int /*<<< orphan*/ * PNTFS_ATTR_RECORD ;
typedef  TYPE_2__* PFIND_ATTR_CONTXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ AttributeAttributeList ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * InternalGetNextAttribute (TYPE_2__*) ; 
 int /*<<< orphan*/  InternalReadNonResidentAttributes (TYPE_2__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_END_OF_FILE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
FindNextAttribute(PFIND_ATTR_CONTXT Context,
                  PNTFS_ATTR_RECORD * Attribute)
{
    NTSTATUS Status;

    DPRINT("FindNextAttribute(%p, %p)\n", Context, Attribute);

    *Attribute = InternalGetNextAttribute(Context);
    if (*Attribute == NULL)
    {
        return STATUS_END_OF_FILE;
    }

    if (Context->CurrAttr->Type != AttributeAttributeList)
    {
        return STATUS_SUCCESS;
    }

    Status = InternalReadNonResidentAttributes(Context);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    *Attribute = InternalGetNextAttribute(Context);
    if (*Attribute == NULL)
    {
        return STATUS_END_OF_FILE;
    }

    return STATUS_SUCCESS;
}