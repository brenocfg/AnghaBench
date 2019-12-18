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
typedef  int mp_usmall ;
typedef  scalar_t__ mp_digit ;

/* Variables and functions */
 int MP_DIGIT_BIT ; 

__attribute__((used)) static int
s_uvpack(mp_usmall uv, mp_digit t[])
{
	int			ndig = 0;

	if (uv == 0)
		t[ndig++] = 0;
	else
	{
		while (uv != 0)
		{
			t[ndig++] = (mp_digit) uv;
			uv >>= MP_DIGIT_BIT / 2;
			uv >>= MP_DIGIT_BIT / 2;
		}
	}

	return ndig;
}