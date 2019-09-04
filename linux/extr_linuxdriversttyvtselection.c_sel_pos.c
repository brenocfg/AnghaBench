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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  inverse_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_glyph (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  screen_glyph_unicode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sel_cons ; 
 scalar_t__ use_unicode ; 

__attribute__((used)) static u32
sel_pos(int n)
{
	if (use_unicode)
		return screen_glyph_unicode(sel_cons, n / 2);
	return inverse_translate(sel_cons, screen_glyph(sel_cons, n),
				0);
}