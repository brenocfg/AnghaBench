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

unsigned int ceph_str_hash_linux(const char *str, unsigned int length)
{
	unsigned long hash = 0;
	unsigned char c;

	while (length--) {
		c = *str++;
		hash = (hash + (c << 4) + (c >> 4)) * 11;
	}
	return hash;
}