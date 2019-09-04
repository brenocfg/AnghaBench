#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long (* gp_diff ) (unsigned long,unsigned long) ;} ;

/* Variables and functions */
 TYPE_1__* cur_ops ; 
 unsigned long stub1 (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long rcutorture_seq_diff(unsigned long new, unsigned long old)
{
	if (!cur_ops->gp_diff)
		return new - old;
	return cur_ops->gp_diff(new, old);
}