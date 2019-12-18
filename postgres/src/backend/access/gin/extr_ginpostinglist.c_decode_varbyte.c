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
typedef  int uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static uint64
decode_varbyte(unsigned char **ptr)
{
	uint64		val;
	unsigned char *p = *ptr;
	uint64		c;

	/* 1st byte */
	c = *(p++);
	val = c & 0x7F;
	if (c & 0x80)
	{
		/* 2nd byte */
		c = *(p++);
		val |= (c & 0x7F) << 7;
		if (c & 0x80)
		{
			/* 3rd byte */
			c = *(p++);
			val |= (c & 0x7F) << 14;
			if (c & 0x80)
			{
				/* 4th byte */
				c = *(p++);
				val |= (c & 0x7F) << 21;
				if (c & 0x80)
				{
					/* 5th byte */
					c = *(p++);
					val |= (c & 0x7F) << 28;
					if (c & 0x80)
					{
						/* 6th byte */
						c = *(p++);
						val |= (c & 0x7F) << 35;
						if (c & 0x80)
						{
							/* 7th byte, should not have continuation bit */
							c = *(p++);
							val |= c << 42;
							Assert((c & 0x80) == 0);
						}
					}
				}
			}
		}
	}

	*ptr = p;

	return val;
}