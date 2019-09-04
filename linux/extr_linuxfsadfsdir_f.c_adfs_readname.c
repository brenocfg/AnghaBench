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

__attribute__((used)) static inline int adfs_readname(char *buf, char *ptr, int maxlen)
{
	char *old_buf = buf;

	while ((unsigned char)*ptr >= ' ' && maxlen--) {
		if (*ptr == '/')
			*buf++ = '.';
		else
			*buf++ = *ptr;
		ptr++;
	}

	return buf - old_buf;
}