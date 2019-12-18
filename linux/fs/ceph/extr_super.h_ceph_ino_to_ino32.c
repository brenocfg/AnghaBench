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
typedef  int u32 ;
typedef  int __u64 ;

/* Variables and functions */

__attribute__((used)) static inline u32 ceph_ino_to_ino32(__u64 vino)
{
	u32 ino = vino & 0xffffffff;
	ino ^= vino >> 32;
	if (!ino)
		ino = 2;
	return ino;
}