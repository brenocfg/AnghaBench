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
struct TYPE_5__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  (* free_fn ) (TYPE_1__*) ;} ;
typedef  TYPE_1__* HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
HPDF_FontDef_Free (HPDF_FontDef  fontdef)
{
    if (!fontdef)
        return;

    HPDF_PTRACE ((" HPDF_FontDef_Free\n"));

    if (fontdef->free_fn)
        fontdef->free_fn (fontdef);
    HPDF_FreeMem (fontdef->mmgr, fontdef);
}