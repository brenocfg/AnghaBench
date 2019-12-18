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
 unsigned int THREAD_ID_MASK ; 
 unsigned int THREAD_ID_SHIFT ; 

__attribute__((used)) static inline unsigned int extract_tid(unsigned int pattern)
{
	unsigned int ret;

	ret = (pattern >> THREAD_ID_SHIFT) & THREAD_ID_MASK;
	return ret;
}