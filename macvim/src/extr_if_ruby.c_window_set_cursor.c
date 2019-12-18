#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  col; int /*<<< orphan*/  lnum; } ;
struct TYPE_5__ {TYPE_1__ w_cursor; } ;
typedef  TYPE_2__ win_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Check_Type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOT_VALID ; 
 int /*<<< orphan*/  NUM2LONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM2UINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Qnil ; 
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_ARRAY ; 
 int /*<<< orphan*/  check_cursor () ; 
 TYPE_2__* get_win (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_eArgError ; 
 int /*<<< orphan*/  rb_raise (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_screen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE window_set_cursor(VALUE self, VALUE pos)
{
    VALUE lnum, col;
    win_T *win = get_win(self);

    Check_Type(pos, T_ARRAY);
    if (RARRAY_LEN(pos) != 2)
	rb_raise(rb_eArgError, "array length must be 2");
    lnum = RARRAY_PTR(pos)[0];
    col = RARRAY_PTR(pos)[1];
    win->w_cursor.lnum = NUM2LONG(lnum);
    win->w_cursor.col = NUM2UINT(col);
    check_cursor();		    /* put cursor on an existing line */
    update_screen(NOT_VALID);
    return Qnil;
}