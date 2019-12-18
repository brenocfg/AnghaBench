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
struct TYPE_9__ {int /*<<< orphan*/  error; int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {scalar_t__ offset; } ;
struct TYPE_7__ {int /*<<< orphan*/  num_glyphs; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__* HPDF_TTFontDefAttr ;
typedef  TYPE_2__ HPDF_TTFTable ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_3__* HPDF_FontDef ;

/* Variables and functions */
 TYPE_2__* FindTable (TYPE_3__*,char*) ; 
 scalar_t__ GetUINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_Stream_Seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_TTF_MISSING_TABLE ; 

__attribute__((used)) static HPDF_STATUS
ParseMaxp (HPDF_FontDef  fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable *tbl = FindTable (fontdef, "maxp");
    HPDF_STATUS ret;

    HPDF_PTRACE ((" HPDF_TTFontDef_ParseMaxp\n"));

    if (!tbl)
        return HPDF_SetError (fontdef->error, HPDF_TTF_MISSING_TABLE, 9);

    ret = HPDF_Stream_Seek (attr->stream, tbl->offset + 4, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    ret = GetUINT16 (attr->stream, &attr->num_glyphs);

    HPDF_PTRACE((" HPDF_TTFontDef_ParseMaxp num_glyphs=%u\n",
            attr->num_glyphs));

    return ret;
}