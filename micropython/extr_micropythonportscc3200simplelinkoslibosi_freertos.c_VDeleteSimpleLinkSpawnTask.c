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
 int /*<<< orphan*/  vQueueDelete (scalar_t__) ; 
 int /*<<< orphan*/  vTaskDelete (scalar_t__) ; 
 scalar_t__ xSimpleLinkSpawnQueue ; 
 scalar_t__ xSimpleLinkSpawnTaskHndl ; 

void VDeleteSimpleLinkSpawnTask( void )
{
	if(xSimpleLinkSpawnTaskHndl)
	{
		vTaskDelete( xSimpleLinkSpawnTaskHndl );
		xSimpleLinkSpawnTaskHndl = 0;
	}

	if(xSimpleLinkSpawnQueue)
	{
		vQueueDelete( xSimpleLinkSpawnQueue );
		xSimpleLinkSpawnQueue = 0;
	}
}