#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sti_cooked_rom {struct sti_cooked_font* font_start; } ;
struct sti_cooked_font {TYPE_1__* raw; struct sti_cooked_font* next_font; } ;
struct TYPE_2__ {int width; int height; } ;

/* Variables and functions */

__attribute__((used)) static int sti_search_font(struct sti_cooked_rom *rom, int height, int width)
{
	struct sti_cooked_font *font;
	int i = 0;
	
	for (font = rom->font_start; font; font = font->next_font, i++) {
		if ((font->raw->width == width) &&
		    (font->raw->height == height))
			return i;
	}
	return 0;
}