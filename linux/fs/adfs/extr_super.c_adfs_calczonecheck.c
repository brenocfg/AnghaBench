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
struct super_block {int s_blocksize; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char adfs_calczonecheck(struct super_block *sb, unsigned char *map)
{
	unsigned int v0, v1, v2, v3;
	int i;

	v0 = v1 = v2 = v3 = 0;
	for (i = sb->s_blocksize - 4; i; i -= 4) {
		v0 += map[i]     + (v3 >> 8);
		v3 &= 0xff;
		v1 += map[i + 1] + (v0 >> 8);
		v0 &= 0xff;
		v2 += map[i + 2] + (v1 >> 8);
		v1 &= 0xff;
		v3 += map[i + 3] + (v2 >> 8);
		v2 &= 0xff;
	}
	v0 +=           v3 >> 8;
	v1 += map[1] + (v0 >> 8);
	v2 += map[2] + (v1 >> 8);
	v3 += map[3] + (v2 >> 8);

	return v0 ^ v1 ^ v2 ^ v3;
}