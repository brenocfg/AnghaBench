#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  str; int /*<<< orphan*/  l; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ textfont_prop_val ;
typedef  int /*<<< orphan*/  fmt ;
typedef  enum textfont_prop_id { ____Placeholder_textfont_prop_id } textfont_prop_id ;
struct TYPE_13__ {int cbSize; int /*<<< orphan*/  szFaceName; int /*<<< orphan*/  wWeight; int /*<<< orphan*/  sSpacing; int /*<<< orphan*/  yHeight; int /*<<< orphan*/  yOffset; int /*<<< orphan*/  lcid; int /*<<< orphan*/  wKerning; int /*<<< orphan*/  crTextColor; int /*<<< orphan*/  crBackColor; void* dwEffects; int /*<<< orphan*/  bAnimation; void* dwMask; } ;
struct TYPE_12__ {int /*<<< orphan*/  editor; } ;
struct TYPE_11__ {int /*<<< orphan*/  range; TYPE_1__* props; scalar_t__ set_cache_enabled; } ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int /*<<< orphan*/  LONG ;
typedef  TYPE_2__ ITextFontImpl ;
typedef  TYPE_3__ IRichEditOleImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ CHARFORMAT2W ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CO_E_RELEASED ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  FONT_ALLCAPS 151 
#define  FONT_ANIMATION 150 
#define  FONT_BACKCOLOR 149 
#define  FONT_BOLD 148 
#define  FONT_EMBOSS 147 
#define  FONT_ENGRAVE 146 
#define  FONT_FORECOLOR 145 
#define  FONT_HIDDEN 144 
#define  FONT_ITALIC 143 
#define  FONT_KERNING 142 
#define  FONT_LANGID 141 
#define  FONT_NAME 140 
#define  FONT_OUTLINE 139 
#define  FONT_POSITION 138 
#define  FONT_PROTECTED 137 
#define  FONT_SHADOW 136 
#define  FONT_SIZE 135 
#define  FONT_SMALLCAPS 134 
#define  FONT_SPACING 133 
#define  FONT_STRIKETHROUGH 132 
#define  FONT_SUBSCRIPT 131 
#define  FONT_SUPERSCRIPT 130 
#define  FONT_UNDERLINE 129 
#define  FONT_WEIGHT 128 
 int /*<<< orphan*/  ITextRange_GetEnd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_CursorFromCharOfs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SetCharFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_range_reole (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 void*** textfont_prop_masks ; 
 int /*<<< orphan*/  tomAutoColor ; 
 int /*<<< orphan*/  tomTrue ; 

__attribute__((used)) static HRESULT set_textfont_prop(ITextFontImpl *font, enum textfont_prop_id propid, const textfont_prop_val *value)
{
    const IRichEditOleImpl *reole;
    ME_Cursor from, to;
    CHARFORMAT2W fmt;
    LONG start, end;

    /* when font is not attached to any range use cache */
    if (!font->range || font->set_cache_enabled) {
        if (propid == FONT_NAME) {
            SysFreeString(font->props[propid].str);
            font->props[propid].str = SysAllocString(value->str);
        }
        else
            font->props[propid] = *value;
        return S_OK;
    }

    if (!(reole = get_range_reole(font->range)))
        return CO_E_RELEASED;

    memset(&fmt, 0, sizeof(fmt));
    fmt.cbSize = sizeof(fmt);
    fmt.dwMask = textfont_prop_masks[propid][0];

    switch (propid)
    {
    case FONT_ALLCAPS:
    case FONT_BOLD:
    case FONT_EMBOSS:
    case FONT_HIDDEN:
    case FONT_ENGRAVE:
    case FONT_ITALIC:
    case FONT_OUTLINE:
    case FONT_PROTECTED:
    case FONT_SHADOW:
    case FONT_SMALLCAPS:
    case FONT_STRIKETHROUGH:
    case FONT_SUBSCRIPT:
    case FONT_SUPERSCRIPT:
    case FONT_UNDERLINE:
        fmt.dwEffects = value->l == tomTrue ? textfont_prop_masks[propid][1] : 0;
        break;
    case FONT_ANIMATION:
        fmt.bAnimation = value->l;
        break;
    case FONT_BACKCOLOR:
    case FONT_FORECOLOR:
        if (value->l == tomAutoColor)
            fmt.dwEffects = textfont_prop_masks[propid][1];
        else if (propid == FONT_BACKCOLOR)
            fmt.crBackColor = value->l;
        else
            fmt.crTextColor = value->l;
        break;
    case FONT_KERNING:
        fmt.wKerning = value->f;
        break;
    case FONT_LANGID:
        fmt.lcid = value->l;
        break;
    case FONT_POSITION:
        fmt.yOffset = value->f;
        break;
    case FONT_SIZE:
        fmt.yHeight = value->f;
        break;
    case FONT_SPACING:
        fmt.sSpacing = value->f;
        break;
    case FONT_WEIGHT:
        fmt.wWeight = value->l;
        break;
    case FONT_NAME:
        lstrcpynW(fmt.szFaceName, value->str, ARRAY_SIZE(fmt.szFaceName));
        break;
    default:
        FIXME("unhandled font property %d\n", propid);
        return E_FAIL;
    }

    ITextRange_GetStart(font->range, &start);
    ITextRange_GetEnd(font->range, &end);

    ME_CursorFromCharOfs(reole->editor, start, &from);
    ME_CursorFromCharOfs(reole->editor, end, &to);
    ME_SetCharFormat(reole->editor, &from, &to, &fmt);

    return S_OK;
}