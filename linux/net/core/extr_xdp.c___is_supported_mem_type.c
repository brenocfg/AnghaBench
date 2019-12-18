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
typedef  enum xdp_mem_type { ____Placeholder_xdp_mem_type } xdp_mem_type ;

/* Variables and functions */
 int MEM_TYPE_MAX ; 
 int MEM_TYPE_PAGE_POOL ; 
 int is_page_pool_compiled_in () ; 

__attribute__((used)) static bool __is_supported_mem_type(enum xdp_mem_type type)
{
	if (type == MEM_TYPE_PAGE_POOL)
		return is_page_pool_compiled_in();

	if (type >= MEM_TYPE_MAX)
		return false;

	return true;
}