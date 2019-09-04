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
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_last_error (int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void push_failure(js_State *J, const char *str)
{
    set_last_error(jctx(J), 1, str);
    js_pushundefined(J);
}