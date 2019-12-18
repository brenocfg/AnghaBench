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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  Latch ;

/* Variables and functions */
 int /*<<< orphan*/  PGINVALID_SOCKET ; 
 int WaitLatchOrSocket (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 

int
WaitLatch(Latch *latch, int wakeEvents, long timeout,
		  uint32 wait_event_info)
{
	return WaitLatchOrSocket(latch, wakeEvents, PGINVALID_SOCKET, timeout,
							 wait_event_info);
}