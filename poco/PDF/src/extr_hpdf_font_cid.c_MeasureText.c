#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_1__ font_bbox; int /*<<< orphan*/  attr; } ;
struct TYPE_17__ {scalar_t__* DW2; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* to_unicode_fn ) (TYPE_4__*,int) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  attr; } ;
struct TYPE_14__ {scalar_t__ writing_mode; TYPE_8__* fontdef; TYPE_4__* encoder; } ;
typedef  int /*<<< orphan*/  HPDF_UNICODE ;
typedef  int HPDF_UINT16 ;
typedef  scalar_t__ HPDF_UINT ;
typedef  int HPDF_REAL ;
typedef  int /*<<< orphan*/  HPDF_ParseText_Rec ;
typedef  scalar_t__ HPDF_INT ;
typedef  TYPE_2__* HPDF_FontAttr ;
typedef  TYPE_3__* HPDF_Font ;
typedef  TYPE_4__* HPDF_Encoder ;
typedef  int HPDF_DOUBLE ;
typedef  TYPE_5__* HPDF_CIDFontDefAttr ;
typedef  scalar_t__ HPDF_ByteType ;
typedef  int HPDF_BYTE ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ HPDF_BYTE_TYPE_LEAD ; 
 scalar_t__ HPDF_BYTE_TYPE_SINGLE ; 
 scalar_t__ HPDF_BYTE_TYPE_TRIAL ; 
 int HPDF_CIDFontDef_GetCIDWidth (TYPE_8__*,int) ; 
 int HPDF_CMapEncoder_ToCID (TYPE_4__*,int) ; 
 scalar_t__ HPDF_Encoder_ByteType (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_Encoder_SetParseText (TYPE_4__*,int /*<<< orphan*/ *,int const*,scalar_t__) ; 
 scalar_t__ HPDF_FONTDEF_TYPE_CID ; 
 scalar_t__ HPDF_IS_WHITE_SPACE (int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int HPDF_TTFontDef_GetCharWidth (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_WMODE_HORIZONTAL ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 

__attribute__((used)) static HPDF_UINT
MeasureText  (HPDF_Font          font,
              const HPDF_BYTE   *text,
              HPDF_UINT          len,
              HPDF_REAL          width,
              HPDF_REAL          font_size,
              HPDF_REAL          char_space,
              HPDF_REAL          word_space,
              HPDF_BOOL          wordwrap,
              HPDF_REAL         *real_width)
{
    HPDF_REAL w = 0;
    HPDF_UINT tmp_len = 0;
    HPDF_UINT i;
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_ByteType last_btype = HPDF_BYTE_TYPE_TRIAL;
    HPDF_Encoder encoder = attr->encoder;
    HPDF_ParseText_Rec  parse_state;
    HPDF_INT dw2;

    HPDF_PTRACE ((" HPDF_Type0Font_MeasureText\n"));

    if (attr->fontdef->type == HPDF_FONTDEF_TYPE_CID) {
        HPDF_CIDFontDefAttr cid_fontdef_attr =
                (HPDF_CIDFontDefAttr)attr->fontdef->attr;
        dw2 = cid_fontdef_attr->DW2[1];
    } else {
        dw2 = (HPDF_INT)(attr->fontdef->font_bbox.bottom -
                    attr->fontdef->font_bbox.top);
    }

    HPDF_Encoder_SetParseText (encoder, &parse_state, text, len);

    for (i = 0; i < len; i++) {
        HPDF_BYTE b = *text++;
        HPDF_BYTE b2 = *text;  /* next byte */
        HPDF_ByteType btype = HPDF_Encoder_ByteType (encoder, &parse_state);
        HPDF_UNICODE unicode;
        HPDF_UINT16 code = b;
        HPDF_UINT16 tmp_w = 0;

        if (btype == HPDF_BYTE_TYPE_LEAD) {
            code <<= 8;
            code = (HPDF_UINT16)(code + b2);
        }

        if (!wordwrap) {
            if (HPDF_IS_WHITE_SPACE(b)) {
                tmp_len = i + 1;
                if (real_width)
                    *real_width = w;
            } else if (btype == HPDF_BYTE_TYPE_SINGLE ||
                        btype == HPDF_BYTE_TYPE_LEAD) {
                tmp_len = i;
                if (real_width)
                    *real_width = w;
            }
        } else {
            if (HPDF_IS_WHITE_SPACE(b)) {
                tmp_len = i + 1;
                if (real_width)
                    *real_width = w;
            } /* else
			//Commenting this out fixes problem with HPDF_Text_Rect() splitting the words
            if (last_btype == HPDF_BYTE_TYPE_TRIAL ||
                    (btype == HPDF_BYTE_TYPE_LEAD &&
                    last_btype == HPDF_BYTE_TYPE_SINGLE)) {
                if (!HPDF_Encoder_CheckJWWLineHead(encoder, code)) {
                    tmp_len = i;
                    if (real_width)
                        *real_width = w;
                }
            }*/
        }

        if (HPDF_IS_WHITE_SPACE(b)) {
            w += word_space;
        }

        if (btype != HPDF_BYTE_TYPE_TRIAL) {
            if (attr->writing_mode == HPDF_WMODE_HORIZONTAL) {
                if (attr->fontdef->type == HPDF_FONTDEF_TYPE_CID) {
                    /* cid-based font */
                    HPDF_UINT16 cid = HPDF_CMapEncoder_ToCID (encoder, code);
                    tmp_w = HPDF_CIDFontDef_GetCIDWidth (attr->fontdef, cid);
                } else {
                    /* unicode-based font */
                    unicode = (encoder->to_unicode_fn)(encoder, code);
                    tmp_w = HPDF_TTFontDef_GetCharWidth (attr->fontdef,
                            unicode);
                }
            } else {
                tmp_w = (HPDF_UINT16)(-dw2);
            }

            if (i > 0)
                w += char_space;
        }

        w += (HPDF_REAL)((HPDF_DOUBLE)tmp_w * font_size / 1000);

        /* 2006.08.04 break when it encountered  line feed */
        if (w > width || b == 0x0A)
            return tmp_len;

        if (HPDF_IS_WHITE_SPACE(b))
            last_btype = HPDF_BYTE_TYPE_TRIAL;
        else
            last_btype = btype;
    }

    /* all of text can be put in the specified width */
    if (real_width)
        *real_width = w;

    return len;
}