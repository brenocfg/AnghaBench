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
struct TYPE_4__ {scalar_t__ count; scalar_t__ block_siz; scalar_t__ items_per_block; void** obj; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_1__* HPDF_List ;

/* Variables and functions */
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ Resize (TYPE_1__*,scalar_t__) ; 

HPDF_STATUS
HPDF_List_Add  (HPDF_List  list,
                void       *item)
{
    HPDF_PTRACE((" HPDF_List_Add\n"));

    if (list->count >= list->block_siz) {
        HPDF_STATUS ret = Resize (list,
                list->block_siz + list->items_per_block);

        if (ret != HPDF_OK) {
            return ret;
        }
    }

    list->obj[list->count++] = item;
    return HPDF_OK;
}