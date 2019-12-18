#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  error; int /*<<< orphan*/  filter; int /*<<< orphan*/  stream; int /*<<< orphan*/  attr; } ;
struct TYPE_18__ {TYPE_2__* fontdef; } ;
struct TYPE_17__ {char* base_font; TYPE_4__* descriptor; int /*<<< orphan*/  x_height; int /*<<< orphan*/  stemv; int /*<<< orphan*/  italic_angle; int /*<<< orphan*/  font_bbox; int /*<<< orphan*/  flags; int /*<<< orphan*/  descent; int /*<<< orphan*/  ascent; int /*<<< orphan*/  attr; } ;
struct TYPE_16__ {char* char_set; int /*<<< orphan*/  length3; int /*<<< orphan*/  length2; int /*<<< orphan*/  length1; scalar_t__ font_data; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  TYPE_1__* HPDF_Type1FontDefAttr ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  TYPE_2__* HPDF_FontDef ;
typedef  TYPE_3__* HPDF_FontAttr ;
typedef  TYPE_4__* HPDF_Font ;
typedef  TYPE_4__* HPDF_Dict ;
typedef  TYPE_4__* HPDF_Array ;

/* Variables and functions */
 TYPE_4__* HPDF_Box_Array_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* HPDF_DictStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_4__*,char*,TYPE_4__*) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_4__*,char*,char*) ; 
 scalar_t__ HPDF_Dict_AddNumber (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_STREAM_FILTER_NONE ; 
 scalar_t__ HPDF_Stream_WriteToStream (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static HPDF_STATUS
Type1Font_CreateDescriptor  (HPDF_MMgr  mmgr,
                             HPDF_Font  font,
                             HPDF_Xref  xref)
{
    HPDF_FontAttr font_attr = (HPDF_FontAttr)font->attr;
    HPDF_FontDef def = font_attr->fontdef;
    HPDF_Type1FontDefAttr def_attr = (HPDF_Type1FontDefAttr)def->attr;

    HPDF_PTRACE ((" HPDF_Type1Font_CreateDescriptor\n"));

    if (!font_attr->fontdef->descriptor) {
        HPDF_Dict descriptor = HPDF_Dict_New (mmgr);
        HPDF_STATUS ret = 0;
        HPDF_Array array;

        if (!descriptor)
            return HPDF_Error_GetCode (font->error);

        ret += HPDF_Xref_Add (xref, descriptor);
        ret += HPDF_Dict_AddName (descriptor, "Type", "FontDescriptor");
        ret += HPDF_Dict_AddNumber (descriptor, "Ascent", def->ascent);
        ret += HPDF_Dict_AddNumber (descriptor, "Descent", def->descent);
        ret += HPDF_Dict_AddNumber (descriptor, "Flags", def->flags);

        array = HPDF_Box_Array_New (mmgr, def->font_bbox);
        ret += HPDF_Dict_Add (descriptor, "FontBBox", array);

        ret += HPDF_Dict_AddName (descriptor, "FontName",
                font_attr->fontdef->base_font);
        ret += HPDF_Dict_AddNumber (descriptor, "ItalicAngle",
                def->italic_angle);
        ret += HPDF_Dict_AddNumber (descriptor, "StemV", def->stemv);
        ret += HPDF_Dict_AddNumber (descriptor, "XHeight", def->x_height);

        if (def_attr->char_set)
            ret += HPDF_Dict_AddName (descriptor, "CharSet",
                        def_attr->char_set);

        if (ret != HPDF_OK)
            return HPDF_Error_GetCode (font->error);

        if (def_attr->font_data) {
            HPDF_Dict font_data = HPDF_DictStream_New (mmgr, xref);

            if (!font_data)
                return HPDF_Error_GetCode (font->error);

            if (HPDF_Stream_WriteToStream (def_attr->font_data,
                font_data->stream, HPDF_STREAM_FILTER_NONE, NULL) != HPDF_OK)
                return HPDF_Error_GetCode (font->error);

            ret += HPDF_Dict_Add (descriptor, "FontFile", font_data);
            ret += HPDF_Dict_AddNumber (font_data, "Length1",
                    def_attr->length1);
            ret += HPDF_Dict_AddNumber (font_data, "Length2",
                    def_attr->length2);
            ret += HPDF_Dict_AddNumber (font_data, "Length3",
                    def_attr->length3);

            font_data->filter = font->filter;
        }

        if (ret != HPDF_OK)
            return HPDF_Error_GetCode (font->error);

        font_attr->fontdef->descriptor = descriptor;
    }

    return HPDF_Dict_Add (font, "FontDescriptor",
            font_attr->fontdef->descriptor);
}