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
 int CMD_BUFF_SIZE ; 
 int /*<<< orphan*/ * arguments ; 
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  cmd_buffer ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int terminal_enabled ; 
 int /*<<< orphan*/  terminal_prompt ; 

void enable_terminal(void) {
    terminal_enabled = true;
    strcpy(buffer, "");
    memset(cmd_buffer, 0, CMD_BUFF_SIZE * 80);
    for (int i = 0; i < 6; i++) strcpy(arguments[i], "");
    // select all text to start over
    // SEND_STRING(SS_LCTRL("a"));
    send_string(terminal_prompt);
}