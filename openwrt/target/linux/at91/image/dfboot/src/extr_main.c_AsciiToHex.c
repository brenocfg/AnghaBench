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

__attribute__((used)) static unsigned int AsciiToHex(char *s, unsigned int *val)
{
	int n;

	*val=0;
	
	if(s[0] == '0' && ((s[1] == 'x') || (s[1] == 'X')))
		s+=2;
	n = 0;	
	while((n < 8) && (s[n] !=0))
	{
		*val <<= 4;
		if ( (s[n] >= '0') && (s[n] <='9'))
			*val += (s[n] - '0');
		else	
			if ((s[n] >= 'a') && (s[n] <='f'))
				*val += (s[n] - 0x57);
			else
				if ((s[n] >= 'A') && (s[n] <='F'))
					*val += (s[n] - 0x37);
			else
				return 0;
		n++;
	}

	return 1;				
}