#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  GISTSearchItem ;
typedef  TYPE_1__* GISTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  pairingheap_is_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ pairingheap_remove_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GISTSearchItem *
getNextGISTSearchItem(GISTScanOpaque so)
{
	GISTSearchItem *item;

	if (!pairingheap_is_empty(so->queue))
	{
		item = (GISTSearchItem *) pairingheap_remove_first(so->queue);
	}
	else
	{
		/* Done when both heaps are empty */
		item = NULL;
	}

	/* Return item; caller is responsible to pfree it */
	return item;
}