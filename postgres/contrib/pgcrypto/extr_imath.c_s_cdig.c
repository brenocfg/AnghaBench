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
typedef  scalar_t__ mp_digit ;

/* Variables and functions */

__attribute__((used)) static int
s_cdig(mp_digit *da, mp_digit *db, mp_size len)
{
	mp_digit   *dat = da + len - 1,
			   *dbt = db + len - 1;

	for ( /* */ ; len != 0; --len, --dat, --dbt)
	{
		if (*dat > *dbt)
		{
			return 1;
		}
		else if (*dat < *dbt)
		{
			return -1;
		}
	}

	return 0;
}