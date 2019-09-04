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
typedef  unsigned int u64 ;

/* Variables and functions */
 unsigned int GENMASK_ULL (unsigned int,int /*<<< orphan*/ ) ; 

unsigned long extract_bytes(u64 data, unsigned int offset,
			    unsigned int num)
{
	return (data >> (offset * 8)) & GENMASK_ULL(num * 8 - 1, 0);
}