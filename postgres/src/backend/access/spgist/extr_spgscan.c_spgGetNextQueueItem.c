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
struct TYPE_3__ {int /*<<< orphan*/  scanQueue; } ;
typedef  int /*<<< orphan*/  SpGistSearchItem ;
typedef  TYPE_1__* SpGistScanOpaque ;

/* Variables and functions */
 scalar_t__ pairingheap_is_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ pairingheap_remove_first (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SpGistSearchItem *
spgGetNextQueueItem(SpGistScanOpaque so)
{
	if (pairingheap_is_empty(so->scanQueue))
		return NULL;			/* Done when both heaps are empty */

	/* Return item; caller is responsible to pfree it */
	return (SpGistSearchItem *) pairingheap_remove_first(so->scanQueue);
}