#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int const nbBits; } ;
typedef  TYPE_1__ HUF_CElt ;

/* Variables and functions */

__attribute__((used)) static size_t HUF_estimateCompressedSize(HUF_CElt *CTable, const unsigned *count, unsigned maxSymbolValue)
{
	size_t nbBits = 0;
	int s;
	for (s = 0; s <= (int)maxSymbolValue; ++s) {
		nbBits += CTable[s].nbBits * count[s];
	}
	return nbBits >> 3;
}