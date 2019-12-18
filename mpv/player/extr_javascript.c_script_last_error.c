#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_2__ {int /*<<< orphan*/  last_error_str; } ;

/* Variables and functions */
 TYPE_1__* jctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void script_last_error(js_State *J)
{
    js_pushstring(J, jctx(J)->last_error_str);
}