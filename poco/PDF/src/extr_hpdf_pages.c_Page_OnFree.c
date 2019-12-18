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
struct TYPE_6__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
struct TYPE_5__ {scalar_t__ gstate; } ;
typedef  TYPE_1__* HPDF_PageAttr ;
typedef  TYPE_2__* HPDF_Dict ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_GState_Free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static void
Page_OnFree  (HPDF_Dict  obj)
{
    HPDF_PageAttr attr = (HPDF_PageAttr)obj->attr;

    HPDF_PTRACE((" HPDF_Page_OnFree\n"));

    if (attr) {
        if (attr->gstate)
            HPDF_GState_Free (obj->mmgr, attr->gstate);

        HPDF_FreeMem (obj->mmgr, attr);
    }
}