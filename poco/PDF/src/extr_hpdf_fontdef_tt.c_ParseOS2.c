#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  error; int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {int offset; } ;
struct TYPE_7__ {scalar_t__ fs_type; int* sfamilyclass; int* panose; scalar_t__ code_page_range2; scalar_t__ code_page_range1; int /*<<< orphan*/  stream; scalar_t__ embedding; } ;
typedef  scalar_t__ HPDF_UINT16 ;
typedef  int HPDF_UINT ;
typedef  TYPE_1__* HPDF_TTFontDefAttr ;
typedef  TYPE_2__ HPDF_TTFTable ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_3__* HPDF_FontDef ;

/* Variables and functions */
 TYPE_2__* FindTable (TYPE_3__*,char*) ; 
 scalar_t__ GetUINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ GetUINT32 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int HPDF_FONT_SCRIPT ; 
 int HPDF_FONT_SERIF ; 
 int HPDF_FONT_SYMBOLIC ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_CUR ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Read (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ HPDF_Stream_Seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_TTF_CANNOT_EMBEDDING_FONT ; 
 int /*<<< orphan*/  HPDF_TTF_MISSING_TABLE ; 

__attribute__((used)) static HPDF_STATUS
ParseOS2  (HPDF_FontDef  fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable *tbl = FindTable (fontdef, "OS/2");
    HPDF_STATUS ret;
    HPDF_UINT16 version;
    HPDF_UINT len;

    HPDF_PTRACE ((" ParseOS2\n"));

    if (!tbl)
        return HPDF_SetError (fontdef->error, HPDF_TTF_MISSING_TABLE, 0);

    /* get the number version. */
    ret = HPDF_Stream_Seek (attr->stream, tbl->offset, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    if ((ret = GetUINT16 (attr->stream, &version)) != HPDF_OK)
        return ret;

    /* check whether the font is allowed to be embedded. */
    ret = HPDF_Stream_Seek (attr->stream, tbl->offset + 8, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    if ((ret = GetUINT16 (attr->stream, &attr->fs_type)) != HPDF_OK)
        return ret;

    if (attr->fs_type  & (0x0002 | 0x0100 | 0x0200) && attr->embedding)
        return HPDF_SetError (fontdef->error, HPDF_TTF_CANNOT_EMBEDDING_FONT,
                0);

    /* get fields sfamilyclass and panose. */
    if ((ret = HPDF_Stream_Seek (attr->stream, tbl->offset + 30, HPDF_SEEK_SET))
            != HPDF_OK)
        return ret;

    len = 2;
    if ((ret = HPDF_Stream_Read (attr->stream, attr->sfamilyclass, &len)) != HPDF_OK)
        return ret;

    len = 10;
    if ((ret = HPDF_Stream_Read (attr->stream, attr->panose, &len)) != HPDF_OK)
        return ret;

    HPDF_PTRACE((" ParseOS2 sFamilyClass=%d-%d "
            "Panose=%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X\n",
        attr->sfamilyclass[0], attr->sfamilyclass[1],
        attr->panose[0], attr->panose[1], attr->panose[2], attr->panose[3],
        attr->panose[4], attr->panose[5], attr->panose[6], attr->panose[7],
        attr->panose[8], attr->panose[9]));

    /* Class ID = 1   Oldstyle Serifs
       Class ID = 2   Transitional Serifs
       Class ID = 3   Modern Serifs
       Class ID = 4   Clarendon Serifs
       Class ID = 5   Slab Serifs
       Class ID = 6   (reserved for future use)
       Class ID = 7   Freeform Serifs
       Class ID = 8   Sans Serif
       Class ID = 9   Ornamentals
       Class ID = 10  Scripts
       Class ID = 11  (reserved for future use)
       Class ID = 12  Symbolic */
    if ((attr->sfamilyclass[0] > 0 && attr->sfamilyclass[0] < 6)
        || (attr->sfamilyclass[0] == 7))
        fontdef->flags = fontdef->flags | HPDF_FONT_SERIF;

    if (attr->sfamilyclass[0] == 10)
        fontdef->flags = fontdef->flags | HPDF_FONT_SCRIPT;

    if (attr->sfamilyclass[0] == 12)
        fontdef->flags = fontdef->flags | HPDF_FONT_SYMBOLIC;

    /* get fields ulCodePageRange1 and ulCodePageRange2 */
    if(version > 0) {
        if ((ret = HPDF_Stream_Seek (attr->stream, 36, HPDF_SEEK_CUR)) != HPDF_OK)
            return ret;

        if ((ret = GetUINT32 (attr->stream, &attr->code_page_range1)) != HPDF_OK)
            return ret;

        if ((ret = GetUINT32 (attr->stream, &attr->code_page_range2)) != HPDF_OK)
            return ret;
    }

    HPDF_PTRACE(("  ParseOS2 CodePageRange1=%08X CodePageRange2=%08X\n",
                (HPDF_UINT)attr->code_page_range1,
                (HPDF_UINT)attr->code_page_range2));

    return HPDF_OK;
}