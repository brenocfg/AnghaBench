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
typedef  int mp_size ;
typedef  int /*<<< orphan*/  mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int* MP_DIGITS (int /*<<< orphan*/ ) ; 
 int MP_DIGIT_BIT ; 
 int MP_USED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
s_isp2(mp_int z)
{
	mp_size		uz = MP_USED(z),
				k = 0;
	mp_digit   *dz = MP_DIGITS(z),
				d;

	while (uz > 1)
	{
		if (*dz++ != 0)
			return -1;
		k += MP_DIGIT_BIT;
		--uz;
	}

	d = *dz;
	while (d > 1)
	{
		if (d & 1)
			return -1;
		++k;
		d >>= 1;
	}

	return (int) k;
}