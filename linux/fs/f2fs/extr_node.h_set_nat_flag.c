#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char flag; } ;
struct nat_entry {TYPE_1__ ni; } ;

/* Variables and functions */

__attribute__((used)) static inline void set_nat_flag(struct nat_entry *ne,
				unsigned int type, bool set)
{
	unsigned char mask = 0x01 << type;
	if (set)
		ne->ni.flag |= mask;
	else
		ne->ni.flag &= ~mask;
}