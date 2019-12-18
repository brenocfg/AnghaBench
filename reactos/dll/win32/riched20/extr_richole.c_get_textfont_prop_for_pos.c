#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* l; void* f; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ textfont_prop_val ;
typedef  int /*<<< orphan*/  fmt ;
typedef  enum textfont_prop_id { ____Placeholder_textfont_prop_id } textfont_prop_id ;
struct TYPE_10__ {int cbSize; int dwMask; int dwEffects; void* crBackColor; void* crTextColor; void* wWeight; void* sSpacing; int /*<<< orphan*/  yHeight; int /*<<< orphan*/  yOffset; int /*<<< orphan*/  szFaceName; void* lcid; int /*<<< orphan*/  wKerning; void* bAnimation; } ;
struct TYPE_9__ {int /*<<< orphan*/  editor; } ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  TYPE_2__ IRichEditOleImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ CHARFORMAT2W ;

/* Variables and functions */
 int CFE_AUTOBACKCOLOR ; 
 int CFE_AUTOCOLOR ; 
 int /*<<< orphan*/  COLOR_WINDOW ; 
 int /*<<< orphan*/  COLOR_WINDOWTEXT ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
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
 void* GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_CursorFromCharOfs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_GetCharFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ME_MoveCursorChars (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int** textfont_prop_masks ; 
 void* tomFalse ; 
 void* tomTrue ; 
 void* twips_to_points (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT get_textfont_prop_for_pos(const IRichEditOleImpl *reole, int pos, enum textfont_prop_id propid,
    textfont_prop_val *value)
{
    ME_Cursor from, to;
    CHARFORMAT2W fmt;

    memset(&fmt, 0, sizeof(fmt));
    fmt.cbSize = sizeof(fmt);
    fmt.dwMask = textfont_prop_masks[propid][0];

    ME_CursorFromCharOfs(reole->editor, pos, &from);
    to = from;
    ME_MoveCursorChars(reole->editor, &to, 1, FALSE);
    ME_GetCharFormat(reole->editor, &from, &to, &fmt);

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
        value->l = fmt.dwEffects & textfont_prop_masks[propid][1] ? tomTrue : tomFalse;
        break;
    case FONT_ANIMATION:
        value->l = fmt.bAnimation;
        break;
    case FONT_BACKCOLOR:
        value->l = fmt.dwEffects & CFE_AUTOBACKCOLOR ? GetSysColor(COLOR_WINDOW) : fmt.crBackColor;
        break;
    case FONT_FORECOLOR:
        value->l = fmt.dwEffects & CFE_AUTOCOLOR ? GetSysColor(COLOR_WINDOWTEXT) : fmt.crTextColor;
        break;
    case FONT_KERNING:
        value->f = twips_to_points(fmt.wKerning);
        break;
    case FONT_LANGID:
        value->l = fmt.lcid;
        break;
    case FONT_NAME:
        /* this case is used exclusively by GetName() */
        value->str = SysAllocString(fmt.szFaceName);
        if (!value->str)
            return E_OUTOFMEMORY;
        break;
    case FONT_POSITION:
        value->f = twips_to_points(fmt.yOffset);
        break;
    case FONT_SIZE:
        value->f = twips_to_points(fmt.yHeight);
        break;
    case FONT_SPACING:
        value->f = fmt.sSpacing;
        break;
    case FONT_WEIGHT:
        value->l = fmt.wWeight;
        break;
    default:
        FIXME("unhandled font property %d\n", propid);
        return E_FAIL;
    }

    return S_OK;
}