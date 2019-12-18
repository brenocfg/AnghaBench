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
 char* SEND_COMMAND (char*) ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  host_get_driver () ; 
 int /*<<< orphan*/  host_set_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_driver ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  rn42_config_driver ; 
 int /*<<< orphan*/  rn42_disconnect () ; 
 scalar_t__ rn42_linked () ; 
 int /*<<< orphan*/  rn42_print_response () ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

__attribute__((used)) static void enter_command_mode(void)
{
    prev_driver = host_get_driver();
    clear_keyboard();
    host_set_driver(&rn42_config_driver);   // null driver; not to send a key to host
    rn42_disconnect();
    while (rn42_linked()) ;

    print("Entering config mode ...\n");
    wait_ms(1100);          // need 1 sec
    SEND_COMMAND("$$$");
    wait_ms(600);           // need 1 sec
    rn42_print_response();
    const char *s = SEND_COMMAND("v\r\n");
    if (strncmp("v", s, 1) != 0) SEND_COMMAND("+\r\n"); // local echo on
}