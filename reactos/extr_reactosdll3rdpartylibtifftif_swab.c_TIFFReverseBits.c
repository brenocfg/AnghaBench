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
typedef  size_t uint8 ;
typedef  int tmsize_t ;

/* Variables and functions */
 size_t* TIFFBitRevTable ; 

void
TIFFReverseBits(uint8* cp, tmsize_t n)  
{
	for (; n > 8; n -= 8) {
		cp[0] = TIFFBitRevTable[cp[0]];
		cp[1] = TIFFBitRevTable[cp[1]];
		cp[2] = TIFFBitRevTable[cp[2]];
		cp[3] = TIFFBitRevTable[cp[3]];
		cp[4] = TIFFBitRevTable[cp[4]];
		cp[5] = TIFFBitRevTable[cp[5]];
		cp[6] = TIFFBitRevTable[cp[6]];
		cp[7] = TIFFBitRevTable[cp[7]];
		cp += 8;
	}
	while (n-- > 0) {
		*cp = TIFFBitRevTable[*cp];
		cp++;
	}
}