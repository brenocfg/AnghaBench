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
typedef  int tableType_t ;
typedef  size_t U32 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
#define  byPtr 130 
#define  byU16 129 
#define  byU32 128 

__attribute__((used)) static void LZ4_putPositionOnHash(
	const BYTE *p,
	U32 h,
	void *tableBase,
	tableType_t const tableType,
	const BYTE *srcBase)
{
	switch (tableType) {
	case byPtr:
	{
		const BYTE **hashTable = (const BYTE **)tableBase;

		hashTable[h] = p;
		return;
	}
	case byU32:
	{
		U32 *hashTable = (U32 *) tableBase;

		hashTable[h] = (U32)(p - srcBase);
		return;
	}
	case byU16:
	{
		U16 *hashTable = (U16 *) tableBase;

		hashTable[h] = (U16)(p - srcBase);
		return;
	}
	}
}