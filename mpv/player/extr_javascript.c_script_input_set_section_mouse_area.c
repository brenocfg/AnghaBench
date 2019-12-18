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
 int /*<<< orphan*/  jsL_checkint (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_input_set_section_mouse_area (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_success (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script_input_set_section_mouse_area(js_State *J)
{
    char *section = (char *)js_tostring(J, 1);
    mp_input_set_section_mouse_area(jctx(J)->mpctx->input, section,
        jsL_checkint(J, 2), jsL_checkint(J, 3),   // x0, y0
        jsL_checkint(J, 4), jsL_checkint(J, 5));  // x1, y1
    push_success(J);
}