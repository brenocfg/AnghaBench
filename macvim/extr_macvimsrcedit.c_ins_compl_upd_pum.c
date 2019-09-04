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
struct TYPE_2__ {int w_cline_height; } ;

/* Variables and functions */
 int /*<<< orphan*/ * compl_match_array ; 
 TYPE_1__* curwin ; 
 int /*<<< orphan*/  ins_compl_del_pum () ; 
 int /*<<< orphan*/  update_screen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ins_compl_upd_pum()
{
    int		h;

    if (compl_match_array != NULL)
    {
	h = curwin->w_cline_height;
	update_screen(0);
	if (h != curwin->w_cline_height)
	    ins_compl_del_pum();
    }
}