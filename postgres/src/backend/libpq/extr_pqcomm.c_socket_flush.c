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
 int internal_flush () ; 
 int /*<<< orphan*/  socket_set_nonblocking (int) ; 

__attribute__((used)) static int
socket_flush(void)
{
	int			res;

	/* No-op if reentrant call */
	if (PqCommBusy)
		return 0;
	PqCommBusy = true;
	socket_set_nonblocking(false);
	res = internal_flush();
	PqCommBusy = false;
	return res;
}