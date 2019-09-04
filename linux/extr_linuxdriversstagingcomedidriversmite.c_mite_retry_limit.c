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
 unsigned int CR_RL (unsigned int) ; 
 int ilog2 (unsigned int) ; 

__attribute__((used)) static unsigned int mite_retry_limit(unsigned int retry_limit)
{
	unsigned int value = 0;

	if (retry_limit)
		value = 1 + ilog2(retry_limit);
	if (value > 0x7)
		value = 0x7;
	return CR_RL(value);
}