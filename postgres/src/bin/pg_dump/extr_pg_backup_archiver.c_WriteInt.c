#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int intSize; int /*<<< orphan*/  (* WriteBytePtr ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int) ; 

size_t
WriteInt(ArchiveHandle *AH, int i)
{
	int			b;

	/*
	 * This is a bit yucky, but I don't want to make the binary format very
	 * dependent on representation, and not knowing much about it, I write out
	 * a sign byte. If you change this, don't forget to change the file
	 * version #, and modify ReadInt to read the new format AS WELL AS the old
	 * formats.
	 */

	/* SIGN byte */
	if (i < 0)
	{
		AH->WriteBytePtr(AH, 1);
		i = -i;
	}
	else
		AH->WriteBytePtr(AH, 0);

	for (b = 0; b < AH->intSize; b++)
	{
		AH->WriteBytePtr(AH, i & 0xFF);
		i >>= 8;
	}

	return AH->intSize + 1;
}