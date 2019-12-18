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
 char* rn42_gets (int) ; 
 int /*<<< orphan*/  rn42_print_response () ; 
 int /*<<< orphan*/  rn42_send_str (char const*) ; 
 int /*<<< orphan*/  wait_ms (int) ; 
 int /*<<< orphan*/  xprintf (char*,char const*) ; 

const char *rn42_send_command(const char *cmd)
{
    static const char *s;
    rn42_send_str(cmd);
    wait_ms(500);
    s = rn42_gets(100);
    xprintf("%s\r\n", s);
    rn42_print_response();
    return s;
}