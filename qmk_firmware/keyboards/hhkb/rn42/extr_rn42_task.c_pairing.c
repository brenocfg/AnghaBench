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
 int /*<<< orphan*/  enter_command_mode () ; 
 int /*<<< orphan*/  exit_command_mode () ; 

__attribute__((used)) static void pairing(void)
{
    enter_command_mode();
    SEND_COMMAND("SR,Z\r\n");   // remove remote address
    SEND_COMMAND("R,1\r\n");    // reboot
    exit_command_mode();
}