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

__attribute__((used)) static char *get_binary(char *buffer, int value)
{
	int i, j, pos;
	pos = 0;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 8; ++j) {
			if (value & (1 << (31-(i*8 + j))))
				buffer[pos] = '1';
			else
				buffer[pos] = '0';
			pos++;
		}
		if (i < 3) {
			buffer[pos] = ' ';
			pos++;
		}
	}
	buffer[pos] = '\0';
	return buffer;
}