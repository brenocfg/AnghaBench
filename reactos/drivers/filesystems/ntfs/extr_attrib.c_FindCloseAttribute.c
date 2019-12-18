#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/ * NonResidentStart; } ;
typedef  TYPE_1__* PFIND_ATTR_CONTXT ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_NTFS ; 

VOID
FindCloseAttribute(PFIND_ATTR_CONTXT Context)
{
    if (Context->NonResidentStart != NULL)
    {
        ExFreePoolWithTag(Context->NonResidentStart, TAG_NTFS);
        Context->NonResidentStart = NULL;
    }
}