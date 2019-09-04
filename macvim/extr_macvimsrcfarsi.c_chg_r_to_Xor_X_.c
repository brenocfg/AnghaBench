#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ col; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  dec_cursor () ; 
 int gchar_cursor () ; 
 int /*<<< orphan*/  inc_cursor () ; 
 int /*<<< orphan*/  p_ri ; 
 int /*<<< orphan*/  put_and_redo (int) ; 
 int toF_Xor_X_ (int) ; 

__attribute__((used)) static void
chg_r_to_Xor_X_()
{
    int tempc, c;

    if (curwin->w_cursor.col)
    {
	if (!p_ri)
	    dec_cursor();

	tempc = gchar_cursor();

	if ((c = toF_Xor_X_(tempc)) != 0)
	    put_and_redo(c);

	if (!p_ri)
	    inc_cursor();

    }
}