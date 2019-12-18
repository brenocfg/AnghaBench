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
typedef  int /*<<< orphan*/ * PNTFS_ATTRIBUTE_LIST_ITEM ;
typedef  int /*<<< orphan*/  PFIND_ATTR_CONTXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/ * InternalGetNextAttributeListItem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 

NTSTATUS
FindNextAttributeListItem(PFIND_ATTR_CONTXT Context,
                          PNTFS_ATTRIBUTE_LIST_ITEM *Item)
{
    *Item = InternalGetNextAttributeListItem(Context);
    if (*Item == NULL)
    {
        return STATUS_UNSUCCESSFUL;
    }
    return STATUS_SUCCESS;
}