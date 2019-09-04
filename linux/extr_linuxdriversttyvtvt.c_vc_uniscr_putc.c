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
struct vc_data {size_t vc_y; size_t vc_x; } ;
struct uni_screen {int /*<<< orphan*/ ** lines; } ;
typedef  int /*<<< orphan*/  char32_t ;

/* Variables and functions */
 struct uni_screen* get_vc_uniscr (struct vc_data*) ; 

__attribute__((used)) static void vc_uniscr_putc(struct vc_data *vc, char32_t uc)
{
	struct uni_screen *uniscr = get_vc_uniscr(vc);

	if (uniscr)
		uniscr->lines[vc->vc_y][vc->vc_x] = uc;
}