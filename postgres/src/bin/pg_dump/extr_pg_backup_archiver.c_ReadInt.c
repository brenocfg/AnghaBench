#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ version; int (* ReadBytePtr ) (TYPE_1__*) ;int intSize; } ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ K_VERS_1_0 ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 

int
ReadInt(ArchiveHandle *AH)
{
	int			res = 0;
	int			bv,
				b;
	int			sign = 0;		/* Default positive */
	int			bitShift = 0;

	if (AH->version > K_VERS_1_0)
		/* Read a sign byte */
		sign = AH->ReadBytePtr(AH);

	for (b = 0; b < AH->intSize; b++)
	{
		bv = AH->ReadBytePtr(AH) & 0xFF;
		if (bv != 0)
			res = res + (bv << bitShift);
		bitShift += 8;
	}

	if (sign)
		res = -res;

	return res;
}