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
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static inline uint32
gb_unlinear(uint32 lin)
{
	uint32		r0 = 0x81 + lin / 12600;
	uint32		r1 = 0x30 + (lin / 1260) % 10;
	uint32		r2 = 0x81 + (lin / 10) % 126;
	uint32		r3 = 0x30 + lin % 10;

	return (r0 << 24) | (r1 << 16) | (r2 << 8) | r3;
}