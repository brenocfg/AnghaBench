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
struct vc_data {int vc_cols; } ;
struct uni_screen {int /*<<< orphan*/ ** lines; } ;

/* Variables and functions */
 struct uni_screen* get_vc_uniscr (struct vc_data*) ; 
 int /*<<< orphan*/  inverse_translate (struct vc_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  screen_glyph (struct vc_data*,int) ; 

u32 screen_glyph_unicode(struct vc_data *vc, int n)
{
	struct uni_screen *uniscr = get_vc_uniscr(vc);

	if (uniscr)
		return uniscr->lines[n / vc->vc_cols][n % vc->vc_cols];
	return inverse_translate(vc, screen_glyph(vc, n * 2), 1);
}