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
typedef  scalar_t__ u16 ;
struct sw_flow_key_range {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static u16 range_n_bytes(const struct sw_flow_key_range *range)
{
	return range->end - range->start;
}