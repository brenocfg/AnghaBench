#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ obj_class; } ;
struct TYPE_7__ {int /*<<< orphan*/  mmgr; TYPE_1__ header; int /*<<< orphan*/  list; } ;
typedef  TYPE_2__* HPDF_Array ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Array_Clear (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_List_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_Array_Free  (HPDF_Array  array)
{
    if (!array)
        return;

    HPDF_PTRACE((" HPDF_Array_Free\n"));

    HPDF_Array_Clear (array);

    HPDF_List_Free (array->list);

    array->header.obj_class = 0;

    HPDF_FreeMem (array->mmgr, array);
}