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
struct eventpoll {int /*<<< orphan*/  ovflist; } ;
struct epitem {int /*<<< orphan*/  next; struct eventpoll* ep; } ;

/* Variables and functions */
 scalar_t__ EP_UNACTIVE_PTR ; 
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,struct epitem*) ; 

__attribute__((used)) static inline bool chain_epi_lockless(struct epitem *epi)
{
	struct eventpoll *ep = epi->ep;

	/* Check that the same epi has not been just chained from another CPU */
	if (cmpxchg(&epi->next, EP_UNACTIVE_PTR, NULL) != EP_UNACTIVE_PTR)
		return false;

	/* Atomically exchange tail */
	epi->next = xchg(&ep->ovflist, epi);

	return true;
}