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

/* Variables and functions */
 int PqCommBusy ; 
 int /*<<< orphan*/  pq_endcopyout (int) ; 

__attribute__((used)) static void
socket_comm_reset(void)
{
	/* Do not throw away pending data, but do reset the busy flag */
	PqCommBusy = false;
	/* We can abort any old-style COPY OUT, too */
	pq_endcopyout(true);
}