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

/* Variables and functions */
 unsigned char inverse_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_glyph (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spk_sel_cons ; 

__attribute__((used)) static unsigned char sel_pos(int n)
{
	return inverse_translate(spk_sel_cons,
		screen_glyph(spk_sel_cons, n), 0);
}