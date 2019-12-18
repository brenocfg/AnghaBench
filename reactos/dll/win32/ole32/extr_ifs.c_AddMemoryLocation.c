#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int SpyedBlockTableLength; int /*<<< orphan*/  SpyedAllocationsLeft; int /*<<< orphan*/ ******* SpyedBlocks; } ;
typedef  int /*<<< orphan*/ **** LPVOID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ Malloc32 ; 
 int /*<<< orphan*/  SetSpyedBlockTableLength (int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL AddMemoryLocation(LPVOID * pMem)
{
        LPVOID * Current;

	/* allocate the table if not already allocated */
        if (!Malloc32.SpyedBlockTableLength && !SetSpyedBlockTableLength(0x1000))
            return FALSE;

	/* find a free location */
	Current = Malloc32.SpyedBlocks;
	while (*Current) {
            Current++;
	    if (Current >= Malloc32.SpyedBlocks + Malloc32.SpyedBlockTableLength) {
	        /* no more space in table, grow it */
                DWORD old_length = Malloc32.SpyedBlockTableLength;
                if (!SetSpyedBlockTableLength( Malloc32.SpyedBlockTableLength + 0x1000))
                    return FALSE;
                Current = Malloc32.SpyedBlocks + old_length;
	    }
	};

	/* put the location in our table */
	*Current = pMem;
        Malloc32.SpyedAllocationsLeft++;
	/*TRACE("%lu\n",Malloc32.SpyedAllocationsLeft);*/
        return TRUE;
}