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
struct TYPE_5__ {int /*<<< orphan*/  mmgr; } ;
typedef  TYPE_1__* HPDF_List ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_List_Clear (TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_List_Free  (HPDF_List  list)
{
    HPDF_PTRACE((" HPDF_List_Free\n"));

    if (!list)
        return ;

    HPDF_List_Clear (list);
    HPDF_FreeMem (list->mmgr, list);
}