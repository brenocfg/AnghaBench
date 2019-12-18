#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* NonResidentCur; TYPE_1__* NonResidentStart; } ;
struct TYPE_5__ {scalar_t__ Type; } ;
typedef  TYPE_1__* PNTFS_ATTRIBUTE_LIST_ITEM ;
typedef  TYPE_2__* PFIND_ATTR_CONTXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ AttributeEnd ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 

NTSTATUS
FindFirstAttributeListItem(PFIND_ATTR_CONTXT Context,
                           PNTFS_ATTRIBUTE_LIST_ITEM *Item)
{
    if (Context->NonResidentStart == NULL || Context->NonResidentStart->Type == AttributeEnd)
    {
        return STATUS_UNSUCCESSFUL;
    }

    Context->NonResidentCur = Context->NonResidentStart;
    *Item = Context->NonResidentCur;
    return STATUS_SUCCESS;
}