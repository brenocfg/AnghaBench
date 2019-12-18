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

__attribute__((used)) static 
unsigned char *
demunge_buf (unsigned char *src, unsigned char *dst, unsigned int src_bytes)

{
	int i;
	unsigned char *end = src + src_bytes;
    
	end = src + src_bytes;

	/* NOTE: src and dst *CAN* point to the same address */

	for (i = 0; src != end; i++) {
		dst[i] = *src++;
		dst[i] |= (*src++)<<7;
	}

	return dst;
}