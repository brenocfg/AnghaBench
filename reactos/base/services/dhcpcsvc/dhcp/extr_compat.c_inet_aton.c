#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t S_addr; } ;
struct in_addr {TYPE_1__ S_un; } ;
typedef  size_t ULONG ;
typedef  char CHAR ;

/* Variables and functions */

int inet_aton(const char *cp, struct in_addr *inp)
/* inet_addr code from ROS, slightly modified. */
{
	ULONG Octets[4] = {0,0,0,0};
	ULONG i = 0;

	if(!cp)
		return 0;

	while(*cp)
	{
		CHAR c = *cp;
		cp++;

		if(c == '.')
		{
			i++;
			continue;
		}

		if(c < '0' || c > '9')
			return 0;

		Octets[i] *= 10;
		Octets[i] += (c - '0');

		if(Octets[i] > 255)
			return 0;
		}

	inp->S_un.S_addr = (Octets[3] << 24) + (Octets[2] << 16) + (Octets[1] << 8) + Octets[0];
	return 1;
}