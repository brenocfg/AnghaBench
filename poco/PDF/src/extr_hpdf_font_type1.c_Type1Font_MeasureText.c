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
struct TYPE_5__ {int /*<<< orphan*/  attr; } ;
struct TYPE_4__ {int* widths; } ;
typedef  size_t HPDF_UINT ;
typedef  int HPDF_REAL ;
typedef  TYPE_1__* HPDF_FontAttr ;
typedef  TYPE_2__* HPDF_Font ;
typedef  size_t HPDF_BYTE ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ HPDF_IS_WHITE_SPACE (size_t) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_UINT
Type1Font_MeasureText (HPDF_Font          font,
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

    HPDF_PTRACE ((" HPDF_Type1Font_MeasureText\n"));

    for (i = 0; i < len; i++) {
        HPDF_BYTE b = text[i];

        if (HPDF_IS_WHITE_SPACE(b)) {
            tmp_len = i + 1;

            if (real_width)
                *real_width = w;

            w += word_space;
        } else if (!wordwrap) {
            tmp_len = i;

            if (real_width)
                *real_width = w;
        }

        w += attr->widths[b] * font_size / 1000;

        /* 2006.08.04 break when it encountered  line feed */
        if (w > width || b == 0x0A)
            return tmp_len;

        if (i > 0)
            w += char_space;
    }

    /* all of text can be put in the specified width */
    if (real_width)
        *real_width = w;

    return len;
}