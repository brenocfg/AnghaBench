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
typedef  unsigned int uint8 ;

/* Variables and functions */
 void** hextbl ; 

__attribute__((used)) static int
print_key(uint8 *keyid, char *dst)
{
	int			i;
	unsigned	c;

	for (i = 0; i < 8; i++)
	{
		c = keyid[i];
		*dst++ = hextbl[(c >> 4) & 0x0F];
		*dst++ = hextbl[c & 0x0F];
	}
	*dst = 0;
	return 8 * 2;
}