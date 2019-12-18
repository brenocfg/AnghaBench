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

char *pstrcpy(char *buf, int buf_size, const char *s)
{
	char *q, *q_end;
	int c;

	if (buf_size > 0) {
		q = buf;
		q_end = buf + buf_size - 1;
		while (q < q_end) {
			c = *s++;
			if (c == '\0') {
				break;
			}
			*q++ = c;
		}
		*q = '\0';
	}
	return buf;
}