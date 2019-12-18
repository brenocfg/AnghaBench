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

/* Variables and functions */
 int /*<<< orphan*/  print (char*) ; 

__attribute__((used)) static void command_console_help(void) {
    print("\n\t- Console -\n"
          "ESC/q:	quit\n"
#ifdef MOUSEKEY_ENABLE
          "m:	mousekey\n"
#endif
    );
}