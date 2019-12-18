#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* top; void* right; void* bottom; void* left; } ;
struct TYPE_13__ {TYPE_1__ font_bbox; int /*<<< orphan*/  error; int /*<<< orphan*/  attr; } ;
struct TYPE_12__ {int /*<<< orphan*/  offset; } ;
struct TYPE_10__ {int flags; int units_per_em; int mac_style; int lowest_rec_ppem; scalar_t__ y_max; scalar_t__ x_max; scalar_t__ y_min; scalar_t__ x_min; scalar_t__ glyph_data_format; scalar_t__ index_to_loc_format; scalar_t__ font_direction_hint; int /*<<< orphan*/ * modified; int /*<<< orphan*/ * created; int /*<<< orphan*/  magic_number; int /*<<< orphan*/  check_sum_adjustment; int /*<<< orphan*/  font_revision; int /*<<< orphan*/  version_number; } ;
struct TYPE_11__ {TYPE_2__ header; int /*<<< orphan*/  stream; } ;
typedef  int HPDF_UINT ;
typedef  TYPE_3__* HPDF_TTFontDefAttr ;
typedef  TYPE_4__ HPDF_TTFTable ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  void* HPDF_REAL ;
typedef  int HPDF_INT32 ;
typedef  TYPE_5__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 TYPE_4__* FindTable (TYPE_5__*,char*) ; 
 scalar_t__ GetINT16 (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ GetUINT16 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GetUINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_Stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ HPDF_Stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_TTF_MISSING_TABLE ; 

__attribute__((used)) static HPDF_STATUS
ParseHead (HPDF_FontDef  fontdef)
{
    HPDF_TTFontDefAttr attr = (HPDF_TTFontDefAttr)fontdef->attr;
    HPDF_TTFTable *tbl = FindTable (fontdef, "head");
    HPDF_STATUS ret;
    HPDF_UINT siz;

    HPDF_PTRACE ((" HPDF_TTFontDef_ParseHead\n"));

    if (!tbl)
        return HPDF_SetError (fontdef->error, HPDF_TTF_MISSING_TABLE, 5);

    ret = HPDF_Stream_Seek (attr->stream, tbl->offset, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    siz = 4;
    ret += HPDF_Stream_Read (attr->stream,
            (HPDF_BYTE *)&attr->header.version_number, &siz);
    ret += GetUINT32 (attr->stream, &attr->header.font_revision);
    ret += GetUINT32 (attr->stream, &attr->header.check_sum_adjustment);
    ret += GetUINT32 (attr->stream, &attr->header.magic_number);
    ret += GetUINT16 (attr->stream, &attr->header.flags);
    ret += GetUINT16 (attr->stream, &attr->header.units_per_em);

    siz = 8;
    ret += HPDF_Stream_Read (attr->stream, attr->header.created, &siz);
    siz = 8;
    ret += HPDF_Stream_Read (attr->stream, attr->header.modified, &siz);

    ret += GetINT16 (attr->stream, &attr->header.x_min);
    ret += GetINT16 (attr->stream, &attr->header.y_min);
    ret += GetINT16 (attr->stream, &attr->header.x_max);
    ret += GetINT16 (attr->stream, &attr->header.y_max);
    ret += GetUINT16 (attr->stream, &attr->header.mac_style);
    ret += GetUINT16 (attr->stream, &attr->header.lowest_rec_ppem);
    ret += GetINT16 (attr->stream, &attr->header.font_direction_hint);
    ret += GetINT16 (attr->stream, &attr->header.index_to_loc_format);
    ret += GetINT16 (attr->stream, &attr->header.glyph_data_format);

    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (fontdef->error);

    fontdef->font_bbox. left = (HPDF_REAL)((HPDF_INT32)attr->header.x_min * 1000 /
                attr->header.units_per_em);
    fontdef->font_bbox. bottom = (HPDF_REAL)((HPDF_INT32)attr->header.y_min * 1000 /
                attr->header.units_per_em);
    fontdef->font_bbox. right = (HPDF_REAL)((HPDF_INT32)attr->header.x_max * 1000 /
                attr->header.units_per_em);
    fontdef->font_bbox. top = (HPDF_REAL)((HPDF_INT32)attr->header.y_max * 1000 /
                attr->header.units_per_em);

    return HPDF_OK;
}