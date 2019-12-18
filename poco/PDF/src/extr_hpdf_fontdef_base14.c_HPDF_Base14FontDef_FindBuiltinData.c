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
struct TYPE_4__ {scalar_t__ font_name; } ;
typedef  size_t HPDF_UINT ;
typedef  TYPE_1__ HPDF_Base14FontDefData ;

/* Variables and functions */
 TYPE_1__ const* HPDF_BUILTIN_FONTS ; 
 scalar_t__ HPDF_StrCmp (scalar_t__,char const*) ; 

const HPDF_Base14FontDefData*
HPDF_Base14FontDef_FindBuiltinData  (const char  *font_name)
{
    HPDF_UINT i = 0;

    while (HPDF_BUILTIN_FONTS[i].font_name) {
        if (HPDF_StrCmp (HPDF_BUILTIN_FONTS[i].font_name, font_name) == 0)
            break;

        i++;
    }

    return &HPDF_BUILTIN_FONTS[i];
}