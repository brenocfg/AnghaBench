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
struct TYPE_3__ {scalar_t__ sig_bytes; } ;
typedef  TYPE_1__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FALSE ; 
 scalar_t__ HPDF_FONTDEF_SIG_BYTES ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_TRUE ; 

HPDF_BOOL
HPDF_FontDef_Validate (HPDF_FontDef  fontdef)
{
    HPDF_PTRACE ((" HPDF_FontDef_Validate\n"));

    if (!fontdef || fontdef->sig_bytes != HPDF_FONTDEF_SIG_BYTES)
        return HPDF_FALSE;
    else
        return HPDF_TRUE;
}