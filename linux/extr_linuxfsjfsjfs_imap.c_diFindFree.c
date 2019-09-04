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
typedef  int u32 ;

/* Variables and functions */
 int HIGHORDER ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int diFindFree(u32 word, int start)
{
	int bitno;
	assert(start < 32);
	/* scan the word for the first free bit. */
	for (word <<= start, bitno = start; bitno < 32;
	     bitno++, word <<= 1) {
		if ((word & HIGHORDER) == 0)
			break;
	}
	return (bitno);
}