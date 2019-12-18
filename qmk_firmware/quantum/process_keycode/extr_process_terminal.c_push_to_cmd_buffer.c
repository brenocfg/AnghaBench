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
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/ * cmd_buffer ; 
 scalar_t__ cmd_buffer_enabled ; 
 int firstTime ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void push_to_cmd_buffer(void) {
    if (cmd_buffer_enabled) {
        if (cmd_buffer == NULL) {
            return;
        } else {
            if (firstTime) {
                firstTime = false;
                strcpy(cmd_buffer[0], buffer);
                return;
            }

            for (int i = CMD_BUFF_SIZE - 1; i > 0; --i) {
                strncpy(cmd_buffer[i], cmd_buffer[i - 1], 80);
            }

            strcpy(cmd_buffer[0], buffer);

            return;
        }
    }
}