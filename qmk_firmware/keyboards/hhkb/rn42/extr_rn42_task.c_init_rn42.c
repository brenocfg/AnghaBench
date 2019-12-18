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
 int /*<<< orphan*/  config_mode ; 
 int /*<<< orphan*/  enter_command_mode () ; 
 int /*<<< orphan*/  exit_command_mode () ; 

__attribute__((used)) static void init_rn42(void)
{
    // RN-42 configure
    if (!config_mode) enter_command_mode();
    SEND_COMMAND("SF,1\r\n");  // factory defaults
    SEND_COMMAND("S-,TmkBT\r\n");
    SEND_COMMAND("SS,Keyboard/Mouse\r\n");
    SEND_COMMAND("SM,4\r\n");  // auto connect(DTR)
    SEND_COMMAND("SW,8000\r\n");   // Sniff disable
    SEND_COMMAND("S~,6\r\n");   // HID profile
    SEND_COMMAND("SH,003C\r\n");   // combo device, out-report, 4-reconnect
    SEND_COMMAND("SY,FFF4\r\n");   // transmit power -12
    SEND_COMMAND("R,1\r\n");
    if (!config_mode) exit_command_mode();
}