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
 unsigned int UINT_MAX ; 
 unsigned int div32 (unsigned int,unsigned int,unsigned int*) ; 

__attribute__((used)) static inline unsigned int div_up(unsigned int a, unsigned int b)
{
	unsigned int r;
	unsigned int q;
	if (b == 0)
		return UINT_MAX;
	q = div32(a, b, &r);
	if (r)
		++q;
	return q;
}