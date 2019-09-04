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
typedef  int /*<<< orphan*/  win_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  NUM2INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curwin ; 
 int /*<<< orphan*/ * get_win (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_setheight (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE window_set_height(VALUE self, VALUE height)
{
    win_T *win = get_win(self);
    win_T *savewin = curwin;

    curwin = win;
    win_setheight(NUM2INT(height));
    curwin = savewin;
    return height;
}