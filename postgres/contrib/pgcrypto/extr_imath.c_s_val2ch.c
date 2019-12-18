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
 int /*<<< orphan*/  assert (int) ; 
 char toupper (unsigned char) ; 

__attribute__((used)) static char
s_val2ch(int v, int caps)
{
	assert(v >= 0);

	if (v < 10)
	{
		return v + '0';
	}
	else
	{
		char		out = (v - 10) + 'a';

		if (caps)
		{
			return toupper((unsigned char) out);
		}
		else
		{
			return out;
		}
	}
}