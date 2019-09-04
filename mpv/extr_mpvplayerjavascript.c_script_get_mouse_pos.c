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
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {TYPE_1__* mpctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 TYPE_2__* jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_input_get_mouse_pos (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  push_nums_obj (int /*<<< orphan*/ *,char const* const*,double const*) ; 

__attribute__((used)) static void script_get_mouse_pos(js_State *J)
{
    int x, y;
    mp_input_get_mouse_pos(jctx(J)->mpctx->input, &x, &y);
    const char * const names[] = {"x", "y", NULL};
    const double vals[] = {x, y};
    push_nums_obj(J, names, vals);
}