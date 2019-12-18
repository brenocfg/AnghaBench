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
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 char* mp_find_config_file (void*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  push_failure (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void script_find_config_file(js_State *J, void *af)
{
    const char *fname = js_tostring(J, 1);
    char *path = mp_find_config_file(af, jctx(J)->mpctx->global, fname);
    if (path) {
        js_pushstring(J, path);
    } else {
        push_failure(J, "not found");
    }
}