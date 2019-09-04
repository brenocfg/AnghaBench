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
 int EMEDIUMTYPE ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static inline int
dasd_check_blocksize(int bsize)
{
	if (bsize < 512 || bsize > 4096 || !is_power_of_2(bsize))
		return -EMEDIUMTYPE;
	return 0;
}