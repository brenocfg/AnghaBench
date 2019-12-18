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
 unsigned int DEVINDEX_HASHBITS ; 
 int DEVINDEX_HASHSIZE ; 

__attribute__((used)) static inline unsigned int fib_devindex_hashfn(unsigned int val)
{
	unsigned int mask = DEVINDEX_HASHSIZE - 1;

	return (val ^
		(val >> DEVINDEX_HASHBITS) ^
		(val >> (DEVINDEX_HASHBITS * 2))) & mask;
}