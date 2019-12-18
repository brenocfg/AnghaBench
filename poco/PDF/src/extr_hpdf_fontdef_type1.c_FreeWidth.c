#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  valid; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * widths; } ;
typedef  TYPE_1__* HPDF_Type1FontDefAttr ;
typedef  TYPE_2__* HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static void
FreeWidth  (HPDF_FontDef  fontdef)
{
    HPDF_Type1FontDefAttr attr = (HPDF_Type1FontDefAttr)fontdef->attr;

    HPDF_PTRACE ((" FreeWidth\n"));

    HPDF_FreeMem (fontdef->mmgr, attr->widths);
    attr->widths = NULL;

    fontdef->valid = HPDF_FALSE;
}