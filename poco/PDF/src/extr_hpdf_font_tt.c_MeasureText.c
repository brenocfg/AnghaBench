#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t HPDF_UINT ;
typedef  int HPDF_REAL ;
typedef  int /*<<< orphan*/  HPDF_Font ;
typedef  int HPDF_DOUBLE ;
typedef  int HPDF_BYTE ;
typedef  int /*<<< orphan*/  HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ CharWidth (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_IS_WHITE_SPACE (int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

__attribute__((used)) static HPDF_UINT
MeasureText (HPDF_Font          font,
             const HPDF_BYTE   *text,
             HPDF_UINT          len,
             HPDF_REAL          width,
             HPDF_REAL          font_size,
             HPDF_REAL          char_space,
             HPDF_REAL          word_space,
             HPDF_BOOL          wordwrap,
             HPDF_REAL         *real_width)
{
    HPDF_DOUBLE w = 0;
    HPDF_UINT tmp_len = 0;
    HPDF_UINT i;

    HPDF_PTRACE ((" HPDF_TTFont_MeasureText\n"));

    for (i = 0; i < len; i++) {
        HPDF_BYTE b = text[i];

        if (HPDF_IS_WHITE_SPACE(b)) {
            tmp_len = i + 1;

            if (real_width)
                *real_width = (HPDF_REAL)w;

            w += word_space;
        } else if (!wordwrap) {
            tmp_len = i;

            if (real_width)
                *real_width = (HPDF_REAL)w;
        }

        w += (HPDF_DOUBLE)CharWidth (font, b) * font_size / 1000;

        /* 2006.08.04 break when it encountered  line feed */
        if (w > width || b == 0x0A)
            return tmp_len;

        if (i > 0)
            w += char_space;
    }

    /* all of text can be put in the specified width */
    if (real_width)
        *real_width = (HPDF_REAL)w;
    return len;
}