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
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* rtfHashTable ; 
 int /*<<< orphan*/  rtfKey ; 

void LookupCleanup(void)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(rtfKey) * 2; i++)
	{
		heap_free( rtfHashTable[i].value );
		rtfHashTable[i].value = NULL;
		rtfHashTable[i].count = 0;
	}
}