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
 scalar_t__ GetPrivateRefCount (int) ; 
 int GetStartupBufferPinWaitBufId () ; 

bool
HoldingBufferPinThatDelaysRecovery(void)
{
	int			bufid = GetStartupBufferPinWaitBufId();

	/*
	 * If we get woken slowly then it's possible that the Startup process was
	 * already woken by other backends before we got here. Also possible that
	 * we get here by multiple interrupts or interrupts at inappropriate
	 * times, so make sure we do nothing if the bufid is not set.
	 */
	if (bufid < 0)
		return false;

	if (GetPrivateRefCount(bufid + 1) > 0)
		return true;

	return false;
}