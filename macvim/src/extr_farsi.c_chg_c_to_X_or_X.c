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
typedef  scalar_t__ colnr_T ;
struct TYPE_3__ {scalar_t__ col; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_CURSOR ; 
 int F_HE ; 
 scalar_t__ F_is_TyB_TyC_TyD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRC_EDT ; 
 scalar_t__ STRLEN (int /*<<< orphan*/ ) ; 
 int _HE_ ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  dec_cursor () ; 
 int gchar_cursor () ; 
 int /*<<< orphan*/  inc_cursor () ; 
 int /*<<< orphan*/  ml_get_curline () ; 
 int /*<<< orphan*/  put_and_redo (int) ; 
 int toF_Xor_X_ (int) ; 

__attribute__((used)) static void
chg_c_to_X_or_X ()
{
    int	tempc;

    tempc = gchar_cursor();

    if (curwin->w_cursor.col + 1 < (colnr_T)STRLEN(ml_get_curline()))
    {
	inc_cursor();

	if ((tempc == F_HE) && (F_is_TyB_TyC_TyD(SRC_EDT, AT_CURSOR)))
	{
	    tempc = _HE_;

	    dec_cursor();

	    put_and_redo(tempc);
	    return;
	}

	dec_cursor();
    }

    if ((tempc = toF_Xor_X_(tempc)) != 0)
	put_and_redo(tempc);
}