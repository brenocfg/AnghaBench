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
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 char const** cmd_buffer ; 
 int /*<<< orphan*/  itoa (int,char*,int) ; 
 int /*<<< orphan*/  send_string (char const*) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void print_cmd_buff(void) {
    /* without the below wait, a race condition can occur wherein the
     buffer can be printed before it has been fully moved */
    wait_ms(250);
    for (int i = 0; i < CMD_BUFF_SIZE; i++) {
        char tmpChar = ' ';
        itoa(i, &tmpChar, 10);
        const char *tmpCnstCharStr = &tmpChar;  // because sned_string wont take a normal char *
        send_string(tmpCnstCharStr);
        SEND_STRING(". ");
        send_string(cmd_buffer[i]);
        SEND_STRING("\n");
    }
}