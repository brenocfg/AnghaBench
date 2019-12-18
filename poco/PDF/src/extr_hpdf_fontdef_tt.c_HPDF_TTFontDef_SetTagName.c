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
struct TYPE_5__ {scalar_t__ base_font; int /*<<< orphan*/  attr; } ;
struct TYPE_4__ {char* tag_name; int* tag_name2; scalar_t__ base_font; } ;
typedef  size_t HPDF_UINT ;
typedef  TYPE_1__* HPDF_TTFontDefAttr ;
typedef  TYPE_2__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int HPDF_LIMIT_MAX_NAME_LEN ; 
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 size_t HPDF_StrLen (char*,int) ; 
 size_t HPDF_TTF_FONT_TAG_LEN ; 

void
HPDF_TTFontDef_SetTagName  (HPDF_FontDef   fontdef,
                            char     *tag)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    char buf[HPDF_LIMIT_MAX_NAME_LEN + 1];
    HPDF_UINT i;

    HPDF_PTRACE ((" HPDF_TTFontDef_SetTagName\n"));

    if (HPDF_StrLen (tag, HPDF_LIMIT_MAX_NAME_LEN) != HPDF_TTF_FONT_TAG_LEN)
        return;

    HPDF_MemCpy ((HPDF_BYTE *)attr->tag_name, (HPDF_BYTE *)tag, HPDF_TTF_FONT_TAG_LEN);
    attr->tag_name[HPDF_TTF_FONT_TAG_LEN] = '+';

    for (i = 0; i < HPDF_TTF_FONT_TAG_LEN + 1; i++) {
        attr->tag_name2[i * 2] = 0x00;
        attr->tag_name2[i * 2 + 1] = attr->tag_name[i];
    }

    HPDF_MemSet (buf, 0, HPDF_LIMIT_MAX_NAME_LEN + 1);
    HPDF_MemCpy ((HPDF_BYTE *)buf, (HPDF_BYTE *)attr->tag_name, HPDF_TTF_FONT_TAG_LEN + 1);
    HPDF_MemCpy ((HPDF_BYTE *)buf + HPDF_TTF_FONT_TAG_LEN + 1, (HPDF_BYTE *)fontdef->base_font, HPDF_LIMIT_MAX_NAME_LEN - HPDF_TTF_FONT_TAG_LEN - 1);

    HPDF_MemCpy ((HPDF_BYTE *)attr->base_font, (HPDF_BYTE *)buf, HPDF_LIMIT_MAX_NAME_LEN + 1);
}