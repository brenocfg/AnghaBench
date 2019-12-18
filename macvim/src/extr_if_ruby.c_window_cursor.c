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
 int /*<<< orphan*/  INT2NUM (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_win (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_assoc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE window_cursor(VALUE self)
{
    win_T *win = get_win(self);

    return rb_assoc_new(INT2NUM(win->w_cursor.lnum), INT2NUM(win->w_cursor.col));
}