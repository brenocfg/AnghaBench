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
 int /*<<< orphan*/  af_subprocess_common (int /*<<< orphan*/ *,int,void*) ; 

__attribute__((used)) static void script_subprocess_detached(js_State *J, void *af)
{
    af_subprocess_common(J, 1, af);
}