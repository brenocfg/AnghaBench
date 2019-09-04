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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ rtas_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  rtascons_get_char_token ; 

__attribute__((used)) static int hvc_rtas_read_console(uint32_t vtermno, char *buf, int count)
{
	int i, c;

	for (i = 0; i < count; i++) {
		if (rtas_call(rtascons_get_char_token, 0, 2, &c))
			break;

		buf[i] = c;
	}

	return i;
}