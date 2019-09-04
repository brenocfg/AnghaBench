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
union bpf_attr {scalar_t__ max_entries; } ;
typedef  int u64 ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 

__attribute__((used)) static u64 dev_map_bitmap_size(const union bpf_attr *attr)
{
	return BITS_TO_LONGS((u64) attr->max_entries) * sizeof(unsigned long);
}