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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  rl_printf (char*,...) ; 

__attribute__((used)) static void hex_dump(const uint8_t *buf, size_t len)
{
	int i;

	rl_printf("%3u: ", 0);
	for (i = 0; i < len; i++) {
		if (i && !(i % 16))
			rl_printf("\n%3u: ", i);
		rl_printf("%02x ", buf[i]);
	}
	rl_printf("\n");
}