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
typedef  int /*<<< orphan*/  __u64 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  array ; 
 long* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab ; 

int func()
{
	__u64 key64 = 0;
	__u32 key = 0;
	long *value;

	value = bpf_map_lookup_elem(&htab, &key);
	if (!value)
		return 1;
	value = bpf_map_lookup_elem(&array, &key64);
	if (!value)
		return 1;

	return 0;
}