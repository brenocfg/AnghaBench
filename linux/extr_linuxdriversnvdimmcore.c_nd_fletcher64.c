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
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

u64 nd_fletcher64(void *addr, size_t len, bool le)
{
	u32 *buf = addr;
	u32 lo32 = 0;
	u64 hi32 = 0;
	int i;

	for (i = 0; i < len / sizeof(u32); i++) {
		lo32 += le ? le32_to_cpu((__le32) buf[i]) : buf[i];
		hi32 += lo32;
	}

	return hi32 << 32 | lo32;
}