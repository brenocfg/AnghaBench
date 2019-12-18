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
struct bitmap {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bs_draw_glyph (int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
draw_glyph(int x, int y, void * glyph, int fgcolor)
{
  struct bitmap * b;

  b = glyph;
  bs_draw_glyph(x, y, (char *)b->data, b->width, b->height, fgcolor);
}