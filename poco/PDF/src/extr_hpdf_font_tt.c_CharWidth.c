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
struct TYPE_4__ {int* used; int /*<<< orphan*/ * widths; int /*<<< orphan*/  fontdef; int /*<<< orphan*/  encoder; } ;
typedef  int /*<<< orphan*/  HPDF_UNICODE ;
typedef  int /*<<< orphan*/  HPDF_INT ;
typedef  TYPE_1__* HPDF_FontAttr ;
typedef  TYPE_2__* HPDF_Font ;
typedef  size_t HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Encoder_ToUnicode (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HPDF_TTFontDef_GetCharWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HPDF_INT
CharWidth (HPDF_Font  font,
           HPDF_BYTE  code)
{
    HPDF_FontAttr attr = (HPDF_FontAttr)font->attr;

    if (attr->used[code] == 0) {
        HPDF_UNICODE unicode = HPDF_Encoder_ToUnicode (attr->encoder, code);

        attr->used[code] = 1;
        attr->widths[code] = HPDF_TTFontDef_GetCharWidth(attr->fontdef,
                unicode);
    }

    return attr->widths[code];
}