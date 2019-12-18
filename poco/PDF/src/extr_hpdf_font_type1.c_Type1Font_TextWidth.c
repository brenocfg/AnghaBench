#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  error; int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {scalar_t__* widths; } ;
struct TYPE_6__ {int /*<<< orphan*/  numwords; int /*<<< orphan*/  numspace; int /*<<< orphan*/  width; int /*<<< orphan*/  numchars; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  size_t HPDF_UINT ;
typedef  TYPE_1__ HPDF_TextWidth ;
typedef  TYPE_2__* HPDF_FontAttr ;
typedef  TYPE_3__* HPDF_Font ;
typedef  size_t HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FONT_INVALID_WIDTHS_TABLE ; 
 scalar_t__ HPDF_IS_WHITE_SPACE (size_t) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_TextWidth
Type1Font_TextWidth  (HPDF_Font        font,
                      const HPDF_BYTE  *text,
                      HPDF_UINT        len)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;
    HPDF_TextWidth ret = {0, 0, 0, 0};
    HPDF_UINT i;
    HPDF_BYTE b = 0;

    HPDF_PTRACE ((" HPDF_Type1Font_TextWidth\n"));

    if (attr->widths) {
        for (i = 0; i < len; i++) {
            b = text[i];
            ret.numchars++;
            ret.width += attr->widths[b];

            if (HPDF_IS_WHITE_SPACE(b)) {
                ret.numspace++;
                ret.numwords++;
            }
        }
    } else
        HPDF_SetError (font->error, HPDF_FONT_INVALID_WIDTHS_TABLE, 0);

    /* 2006.08.19 add. */
    if (HPDF_IS_WHITE_SPACE(b))
        ; /* do nothing. */
    else
        ret.numwords++;

    return ret;
}