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
struct nd_btt {scalar_t__ initial_offset; } ;

/* Variables and functions */

__attribute__((used)) static u64 adjust_initial_offset(struct nd_btt *nd_btt, u64 offset)
{
	return offset + nd_btt->initial_offset;
}