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
struct TYPE_3__ {size_t count; void** obj; } ;
typedef  size_t HPDF_UINT ;
typedef  TYPE_1__* HPDF_List ;
typedef  size_t HPDF_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_INT32
HPDF_List_Find  (HPDF_List  list,
                 void       *item)
{
    HPDF_UINT i;

    HPDF_PTRACE((" HPDF_List_Find\n"));

    for (i = 0; i < list->count; i++) {
        if (list->obj[i] == item)
            return i;
    }

    return -1;
}