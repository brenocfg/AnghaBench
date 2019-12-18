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
 unsigned short READ_SHORT (unsigned char*,long) ; 

unsigned short checksum(unsigned char *data, long size)
{
	long n;
	unsigned short d, cs = 0;
	for (n = 0; n < size; n += 2)
	{
		d = READ_SHORT(data, n);
		cs += d;
		if (cs < d)
			cs++;
	}
	if (size & 1)
	{
		d = data[n];
		cs += d;
		if (cs < d)
			cs++;
	}
	return cs;
}