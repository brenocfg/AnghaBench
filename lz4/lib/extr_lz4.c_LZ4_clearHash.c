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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
#define  byPtr 131 
#define  byU16 130 
#define  byU32 129 
#define  clearedTable 128 

__attribute__((used)) static void LZ4_clearHash(U32 h, void* tableBase, tableType_t const tableType)
{
    switch (tableType)
    {
    default: /* fallthrough */
    case clearedTable: { /* illegal! */ assert(0); return; }
    case byPtr: { const BYTE** hashTable = (const BYTE**)tableBase; hashTable[h] = NULL; return; }
    case byU32: { U32* hashTable = (U32*) tableBase; hashTable[h] = 0; return; }
    case byU16: { U16* hashTable = (U16*) tableBase; hashTable[h] = 0; return; }
    }
}