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
typedef  int __u32 ;

/* Variables and functions */
#define  BTF_VAR_GLOBAL_ALLOCATED 129 
#define  BTF_VAR_STATIC 128 

__attribute__((used)) static const char *btf_var_linkage_str(__u32 linkage)
{
	switch (linkage) {
	case BTF_VAR_STATIC:
		return "static";
	case BTF_VAR_GLOBAL_ALLOCATED:
		return "global-alloc";
	default:
		return "(unknown)";
	}
}