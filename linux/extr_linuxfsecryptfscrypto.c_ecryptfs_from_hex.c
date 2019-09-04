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
 scalar_t__ simple_strtol (char*,int /*<<< orphan*/ *,int) ; 

void ecryptfs_from_hex(char *dst, char *src, int dst_size)
{
	int x;
	char tmp[3] = { 0, };

	for (x = 0; x < dst_size; x++) {
		tmp[0] = src[x * 2];
		tmp[1] = src[x * 2 + 1];
		dst[x] = (unsigned char)simple_strtol(tmp, NULL, 16);
	}
}