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

/* Variables and functions */
 int EINVAL ; 
 unsigned int TRIG_INVALID ; 

__attribute__((used)) static inline int comedi_check_trigger_src(unsigned int *src,
					   unsigned int flags)
{
	unsigned int orig_src = *src;

	*src = orig_src & flags;
	if (*src == TRIG_INVALID || *src != orig_src)
		return -EINVAL;
	return 0;
}