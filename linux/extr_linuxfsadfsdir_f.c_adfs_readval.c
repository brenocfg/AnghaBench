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

__attribute__((used)) static inline unsigned int adfs_readval(unsigned char *p, int len)
{
	unsigned int val = 0;

	switch (len) {
	case 4:		val |= p[3] << 24;
	case 3:		val |= p[2] << 16;
	case 2:		val |= p[1] << 8;
	default:	val |= p[0];
	}
	return val;
}