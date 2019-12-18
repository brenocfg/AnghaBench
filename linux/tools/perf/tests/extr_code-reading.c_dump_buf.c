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
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void dump_buf(unsigned char *buf, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		pr_debug("0x%02x ", buf[i]);
		if (i % 16 == 15)
			pr_debug("\n");
	}
	pr_debug("\n");
}