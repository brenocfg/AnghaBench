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
 int /*<<< orphan*/  js_gc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_success (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script__gc(js_State *J)
{
    js_gc(J, js_toboolean(J, 1) ? 1 : 0);
    push_success(J);
}