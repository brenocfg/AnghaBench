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
typedef  scalar_t__ tableType_t ;
typedef  size_t U32 ;
typedef  int U16 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ byPtr ; 
 scalar_t__ byU32 ; 

__attribute__((used)) static const BYTE *LZ4_getPositionOnHash(
	U32 h,
	void *tableBase,
	tableType_t tableType,
	const BYTE *srcBase)
{
	if (tableType == byPtr) {
		const BYTE **hashTable = (const BYTE **) tableBase;

		return hashTable[h];
	}

	if (tableType == byU32) {
		const U32 * const hashTable = (U32 *) tableBase;

		return hashTable[h] + srcBase;
	}

	{
		/* default, to ensure a return */
		const U16 * const hashTable = (U16 *) tableBase;

		return hashTable[h] + srcBase;
	}
}