#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HPDF_UNICODE ;
typedef  int /*<<< orphan*/  HPDF_INT16 ;
typedef  int /*<<< orphan*/  HPDF_FontDef ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_GryphNameToUnicode (char const*) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_Type1FontDef_GetWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_INT16
HPDF_Type1FontDef_GetWidthByName  (HPDF_FontDef      fontdef,
                                   const char*  gryph_name)
{
    HPDF_UNICODE unicode = HPDF_GryphNameToUnicode (gryph_name);

    HPDF_PTRACE ((" HPDF_Type1FontDef_GetWidthByName\n"));

    return HPDF_Type1FontDef_GetWidth (fontdef, unicode);
}