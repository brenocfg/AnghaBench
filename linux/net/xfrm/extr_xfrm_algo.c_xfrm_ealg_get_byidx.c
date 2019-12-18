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
struct xfrm_algo_desc {int dummy; } ;

/* Variables and functions */
 unsigned int ealg_entries () ; 
 struct xfrm_algo_desc* ealg_list ; 

struct xfrm_algo_desc *xfrm_ealg_get_byidx(unsigned int idx)
{
	if (idx >= ealg_entries())
		return NULL;

	return &ealg_list[idx];
}