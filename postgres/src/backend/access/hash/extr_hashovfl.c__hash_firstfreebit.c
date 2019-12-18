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
typedef  scalar_t__ uint32 ;

/* Variables and functions */
 scalar_t__ BITS_PER_MAP ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint32
_hash_firstfreebit(uint32 map)
{
	uint32		i,
				mask;

	mask = 0x1;
	for (i = 0; i < BITS_PER_MAP; i++)
	{
		if (!(mask & map))
			return i;
		mask <<= 1;
	}

	elog(ERROR, "firstfreebit found no free bit");

	return 0;					/* keep compiler quiet */
}