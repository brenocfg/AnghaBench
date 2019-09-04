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
struct phy_txts {int sec_lo; int sec_hi; int ns_lo; int ns_hi; } ;

/* Variables and functions */

__attribute__((used)) static u64 phy2txts(struct phy_txts *p)
{
	u64 ns;
	u32 sec;

	sec = p->sec_lo;
	sec |= p->sec_hi << 16;

	ns = p->ns_lo;
	ns |= (p->ns_hi & 0x3fff) << 16;
	ns += ((u64)sec) * 1000000000ULL;

	return ns;
}