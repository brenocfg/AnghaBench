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
 unsigned long htotal ; 
 int /*<<< orphan*/  prefetch (void*) ; 

void hash_zone(void *zone, unsigned int length)
{
	unsigned long temp = htotal;

	while (length >= 8*sizeof(long)) {
		prefetch(zone + 384);
		temp ^= *(unsigned long *)zone;
		temp ^= *(unsigned long *)(zone + sizeof(long));
		temp ^= *(unsigned long *)(zone + 2*sizeof(long));
		temp ^= *(unsigned long *)(zone + 3*sizeof(long));
		temp ^= *(unsigned long *)(zone + 4*sizeof(long));
		temp ^= *(unsigned long *)(zone + 5*sizeof(long));
		temp ^= *(unsigned long *)(zone + 6*sizeof(long));
		temp ^= *(unsigned long *)(zone + 7*sizeof(long));
		zone += 8*sizeof(long);
		length -= 8*sizeof(long);
	}
	while (length >= 1) {
		temp ^= *(unsigned char *)zone;
		zone += 1;
		length--;
	}
	htotal = temp;
}