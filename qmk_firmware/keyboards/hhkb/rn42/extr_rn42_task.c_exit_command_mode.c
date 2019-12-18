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
 int /*<<< orphan*/  SEND_COMMAND (char*) ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prev_driver ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  rn42_autoconnect () ; 

__attribute__((used)) static void exit_command_mode(void)
{
    print("Exiting config mode ...\n");
    SEND_COMMAND("---\r\n");    // exit

    rn42_autoconnect();
    clear_keyboard();
    host_set_driver(prev_driver);
}