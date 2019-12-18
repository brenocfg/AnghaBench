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
typedef  int pgoff_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* WriteBytePtr ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int) ; 

size_t
WriteOffset(ArchiveHandle *AH, pgoff_t o, int wasSet)
{
	int			off;

	/* Save the flag */
	AH->WriteBytePtr(AH, wasSet);

	/* Write out pgoff_t smallest byte first, prevents endian mismatch */
	for (off = 0; off < sizeof(pgoff_t); off++)
	{
		AH->WriteBytePtr(AH, o & 0xFF);
		o >>= 8;
	}
	return sizeof(pgoff_t) + 1;
}