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
struct vc_data {scalar_t__ vc_mode; int vc_cursor_type; TYPE_1__* vc_sw; scalar_t__ vc_deccm; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* con_cursor ) (struct vc_data*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DRAW ; 
 scalar_t__ KD_GRAPHICS ; 
 int /*<<< orphan*/  add_softcursor (struct vc_data*) ; 
 int /*<<< orphan*/  clear_selection () ; 
 int /*<<< orphan*/  con_is_fg (struct vc_data*) ; 
 scalar_t__ console_blanked ; 
 int /*<<< orphan*/  hide_cursor (struct vc_data*) ; 
 struct vc_data* sel_cons ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_cursor(struct vc_data *vc)
{
	if (!con_is_fg(vc) || console_blanked || vc->vc_mode == KD_GRAPHICS)
		return;
	if (vc->vc_deccm) {
		if (vc == sel_cons)
			clear_selection();
		add_softcursor(vc);
		if ((vc->vc_cursor_type & 0x0f) != 1)
			vc->vc_sw->con_cursor(vc, CM_DRAW);
	} else
		hide_cursor(vc);
}