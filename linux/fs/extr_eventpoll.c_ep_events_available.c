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
struct eventpoll {int /*<<< orphan*/  ovflist; int /*<<< orphan*/  rdllist; } ;

/* Variables and functions */
 scalar_t__ EP_UNACTIVE_PTR ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ep_events_available(struct eventpoll *ep)
{
	return !list_empty_careful(&ep->rdllist) ||
		READ_ONCE(ep->ovflist) != EP_UNACTIVE_PTR;
}