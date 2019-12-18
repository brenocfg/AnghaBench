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
struct vringh_range {scalar_t__ offset; scalar_t__ end_incl; scalar_t__ start; } ;
struct vringh {int dummy; } ;

/* Variables and functions */
 scalar_t__ __user_addr_max ; 
 scalar_t__ __user_addr_min ; 
 scalar_t__ user_addr_offset ; 

__attribute__((used)) static bool getrange_iov(struct vringh *vrh, u64 addr, struct vringh_range *r)
{
	if (addr < (u64)(unsigned long)__user_addr_min - user_addr_offset)
		return false;
	if (addr >= (u64)(unsigned long)__user_addr_max - user_addr_offset)
		return false;

	r->start = (u64)(unsigned long)__user_addr_min - user_addr_offset;
	r->end_incl = (u64)(unsigned long)__user_addr_max - 1 - user_addr_offset;
	r->offset = user_addr_offset;
	return true;
}