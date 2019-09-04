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
typedef  scalar_t__ u64 ;

/* Variables and functions */

__attribute__((used)) static u64 rb_space_to_end(u64 wr, u64 rd, u64 len)
{
	if (rd > wr)
		return rd - wr - 8;
	else if (rd > 0)
		return len - wr;
	else
		return len - wr - 8;
}