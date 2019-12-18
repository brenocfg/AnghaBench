#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  font; } ;
typedef  TYPE_1__ FONSttFontImpl ;

/* Variables and functions */
 int /*<<< orphan*/  stbtt_GetFontVMetrics (int /*<<< orphan*/ *,int*,int*,int*) ; 

void fons__tt_getFontVMetrics(FONSttFontImpl *font, int *ascent, int *descent, int *lineGap)
{
	stbtt_GetFontVMetrics(&font->font, ascent, descent, lineGap);
}