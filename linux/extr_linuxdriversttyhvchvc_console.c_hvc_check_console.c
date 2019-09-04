#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int index; } ;

/* Variables and functions */
 int CON_ENABLED ; 
 TYPE_1__ hvc_console ; 
 int /*<<< orphan*/  register_console (TYPE_1__*) ; 

__attribute__((used)) static void hvc_check_console(int index)
{
	/* Already enabled, bail out */
	if (hvc_console.flags & CON_ENABLED)
		return;

 	/* If this index is what the user requested, then register
	 * now (setup won't fail at this point).  It's ok to just
	 * call register again if previously .setup failed.
	 */
	if (index == hvc_console.index)
		register_console(&hvc_console);
}