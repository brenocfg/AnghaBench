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
struct TYPE_3__ {int /*<<< orphan*/  global; } ;

/* Variables and functions */
 TYPE_2__* jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_get_user_path (void*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void script_get_user_path(js_State *J, void *af)
{
    const char *path = js_tostring(J, 1);
    js_pushstring(J, mp_get_user_path(af, jctx(J)->mpctx->global, path));
}