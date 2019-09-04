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
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void script_getenv(js_State *J)
{
    const char *v = getenv(js_tostring(J, 1));
    if (v) {
        js_pushstring(J, v);
    } else {
        js_pushundefined(J);
    }
}