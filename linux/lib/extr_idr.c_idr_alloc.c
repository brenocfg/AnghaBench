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
typedef  int u32 ;
struct idr {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int idr_alloc_u32 (struct idr*,void*,int*,int,int /*<<< orphan*/ ) ; 

int idr_alloc(struct idr *idr, void *ptr, int start, int end, gfp_t gfp)
{
	u32 id = start;
	int ret;

	if (WARN_ON_ONCE(start < 0))
		return -EINVAL;

	ret = idr_alloc_u32(idr, ptr, &id, end > 0 ? end - 1 : INT_MAX, gfp);
	if (ret)
		return ret;

	return id;
}