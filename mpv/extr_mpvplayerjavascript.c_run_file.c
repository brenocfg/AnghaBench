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
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_loadstring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_file_content (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void run_file(js_State *J, const char *fname)
{
    MP_VERBOSE(jctx(J), "Loading file %s\n", fname);
    push_file_content(J, fname, -1);
    js_loadstring(J, fname, js_tostring(J, -1));
    js_copy(J, 0);  // use the caller's this
    js_call(J, 0);
    js_pop(J, 2);  // result, file content
}