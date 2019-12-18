#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  w_height; } ;
typedef  TYPE_1__ win_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  INT2NUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_win (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE window_height(VALUE self)
{
    win_T *win = get_win(self);

    return INT2NUM(win->w_height);
}