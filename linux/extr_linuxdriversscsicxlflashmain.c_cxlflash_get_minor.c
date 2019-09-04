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
 long CXLFLASH_MAX_ADAPTERS ; 
 long MINORMASK ; 
 int /*<<< orphan*/  cxlflash_minor ; 
 long find_first_zero_bit (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxlflash_get_minor(void)
{
	int minor;
	long bit;

	bit = find_first_zero_bit(cxlflash_minor, CXLFLASH_MAX_ADAPTERS);
	if (bit >= CXLFLASH_MAX_ADAPTERS)
		return -1;

	minor = bit & MINORMASK;
	set_bit(minor, cxlflash_minor);
	return minor;
}