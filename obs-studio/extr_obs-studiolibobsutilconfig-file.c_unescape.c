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
struct dstr {char* array; } ;

/* Variables and functions */

__attribute__((used)) static void unescape(struct dstr *str)
{
	char *read = str->array;
	char *write = str->array;

	for (; *read; read++, write++) {
		char cur = *read;
		if (cur == '\\') {
			char next = read[1];
			if (next == '\\') {
				read++;
			} else if (next == 'r') {
				cur = '\r';
				read++;
			} else if (next =='n') {
				cur = '\n';
				read++;
			}
		}

		if (read != write)
			*write = cur;
	}

	if (read != write)
		*write = '\0';
}