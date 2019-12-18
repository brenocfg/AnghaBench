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
struct wavefront_command {int cmd; } ;

/* Variables and functions */
 struct wavefront_command* wavefront_commands ; 

__attribute__((used)) static struct wavefront_command *
wavefront_get_command (int cmd) 

{
	int i;

	for (i = 0; wavefront_commands[i].cmd != 0; i++) {
		if (cmd == wavefront_commands[i].cmd) {
			return &wavefront_commands[i];
		}
	}

	return NULL;
}