#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  error; void* descent; void* ascent; int /*<<< orphan*/  attr; } ;
struct TYPE_10__ {scalar_t__ offset; } ;
struct TYPE_8__ {int units_per_em; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_h_metric; int /*<<< orphan*/  stream; TYPE_1__ header; } ;
typedef  TYPE_2__* HPDF_TTFontDefAttr ;
typedef  TYPE_3__ HPDF_TTFTable ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int HPDF_INT32 ;
typedef  void* HPDF_INT16 ;
typedef  TYPE_4__* HPDF_FontDef ;

/* Variables and functions */
 TYPE_3__* FindTable (TYPE_4__*,char*) ; 
 scalar_t__ GetINT16 (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ GetUINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_Stream_Seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_TTF_MISSING_TABLE ; 

__attribute__((used)) static HPDF_STATUS
ParseHhea (HPDF_FontDef  fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable *tbl = FindTable (fontdef, "hhea");
    HPDF_STATUS ret;

    HPDF_PTRACE ((" HPDF_TTFontDef_ParseHhea\n"));

    if (!tbl)
        return HPDF_SetError (fontdef->error, HPDF_TTF_MISSING_TABLE, 6);

    ret = HPDF_Stream_Seek (attr->stream, tbl->offset + 4, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    ret += GetINT16 (attr->stream, &fontdef->ascent);
    fontdef->ascent = (HPDF_INT16)((HPDF_INT32)fontdef->ascent * 1000 /
                attr->header.units_per_em);
    ret += GetINT16 (attr->stream, &fontdef->descent);
    fontdef->descent = (HPDF_INT16)((HPDF_INT32)fontdef->descent * 1000 /
                attr->header.units_per_em);

    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (fontdef->error);

    ret = HPDF_Stream_Seek (attr->stream, tbl->offset + 34, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    ret = GetUINT16 (attr->stream, &attr->num_h_metric);
    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (fontdef->error);

    HPDF_PTRACE((" HPDF_TTFontDef_ParseHhea num_h_metric=%u\n",
            attr->num_h_metric));

    return ret;
}