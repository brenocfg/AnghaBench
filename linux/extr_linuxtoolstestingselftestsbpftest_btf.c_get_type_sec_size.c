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
typedef  int /*<<< orphan*/  raw_types ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ const BTF_END_RAW ; 
 int MAX_NR_RAW_TYPES ; 

__attribute__((used)) static int get_type_sec_size(const __u32 *raw_types)
{
	int i;

	for (i = MAX_NR_RAW_TYPES - 1;
	     i >= 0 && raw_types[i] != BTF_END_RAW;
	     i--)
		;

	return i < 0 ? i : i * sizeof(raw_types[0]);
}