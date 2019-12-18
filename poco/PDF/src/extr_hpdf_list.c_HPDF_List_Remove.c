#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void** obj; scalar_t__ count; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_List ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_ITEM_NOT_FOUND ; 
 int /*<<< orphan*/  HPDF_List_RemoveByIndex (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_List_Remove  (HPDF_List  list,
                   void       *item)
{
    HPDF_UINT i;
    void **obj = list->obj;

    HPDF_PTRACE((" HPDF_List_Remove\n"));

    for (i = 0; i < list->count; i++) {
        if (*obj == item) {
            HPDF_List_RemoveByIndex(list, i);
            return HPDF_OK;
        } else
            obj++;
    }

    return HPDF_ITEM_NOT_FOUND;
}