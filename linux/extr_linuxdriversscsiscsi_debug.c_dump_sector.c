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
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ scnprintf (char*,int,char*,unsigned char) ; 

__attribute__((used)) static void dump_sector(unsigned char *buf, int len)
{
	int i, j, n;

	pr_err(">>> Sector Dump <<<\n");
	for (i = 0 ; i < len ; i += 16) {
		char b[128];

		for (j = 0, n = 0; j < 16; j++) {
			unsigned char c = buf[i+j];

			if (c >= 0x20 && c < 0x7e)
				n += scnprintf(b + n, sizeof(b) - n,
					       " %c ", buf[i+j]);
			else
				n += scnprintf(b + n, sizeof(b) - n,
					       "%02x ", buf[i+j]);
		}
		pr_err("%04d: %s\n", i, b);
	}
}