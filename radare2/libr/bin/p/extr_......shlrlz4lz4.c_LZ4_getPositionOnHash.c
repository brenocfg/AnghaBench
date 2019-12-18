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
typedef  int /*<<< orphan*/  ut8 ;
typedef  size_t ut32 ;
typedef  int ut16 ;
typedef  scalar_t__ tableType_t ;

/* Variables and functions */
 scalar_t__ byPtr ; 
 scalar_t__ byut32 ; 

__attribute__((used)) static const ut8* LZ4_getPositionOnHash(ut32 h, void* tableBase, tableType_t tableType, const ut8* srcBase) {
	if (tableType == byPtr) { const ut8** hashTable = (const ut8**) tableBase; return hashTable[h]; }
	if (tableType == byut32) { const ut32* const hashTable = (ut32*) tableBase; return hashTable[h] + srcBase; }
	{ const ut16* const hashTable = (ut16*) tableBase; return hashTable[h] + srcBase; }   /* default, to ensure a return */
}