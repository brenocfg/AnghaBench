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
typedef  int /*<<< orphan*/  ut16 ;
typedef  int tableType_t ;

/* Variables and functions */
#define  byPtr 130 
#define  byut16 129 
#define  byut32 128 

__attribute__((used)) static void LZ4_putPositionOnHash(const ut8* p, ut32 h, void* tableBase, tableType_t const tableType, const ut8* srcBase) {
	switch (tableType) {
	case byPtr: { const ut8** hashTable = (const ut8**)tableBase; hashTable[h] = p; return; }
	case byut32: { ut32* hashTable = (ut32*) tableBase; hashTable[h] = (ut32)(p-srcBase); return; }
	case byut16: { ut16* hashTable = (ut16*) tableBase; hashTable[h] = (ut16)(p-srcBase); return; }
	}
}