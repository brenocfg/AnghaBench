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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mpv_error_string (int) ; 
 int /*<<< orphan*/  set_last_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool pushed_error(js_State *J, int err, int def)
{
    bool iserr = err < 0;
    set_last_error(jctx(J), iserr, iserr ? mpv_error_string(err) : NULL);
    if (!iserr)
        return false;

    js_copy(J, def);
    return true;
}