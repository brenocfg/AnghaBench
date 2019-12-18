#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {TYPE_1__** scanEntry; } ;
struct TYPE_3__ {scalar_t__ predictNumberResult; } ;
typedef  TYPE_2__* GinScanKey ;

/* Variables and functions */

__attribute__((used)) static int
entryIndexByFrequencyCmp(const void *a1, const void *a2, void *arg)
{
	const GinScanKey key = (const GinScanKey) arg;
	int			i1 = *(const int *) a1;
	int			i2 = *(const int *) a2;
	uint32		n1 = key->scanEntry[i1]->predictNumberResult;
	uint32		n2 = key->scanEntry[i2]->predictNumberResult;

	if (n1 < n2)
		return -1;
	else if (n1 == n2)
		return 0;
	else
		return 1;
}