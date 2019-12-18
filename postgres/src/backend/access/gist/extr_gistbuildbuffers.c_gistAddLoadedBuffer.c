#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t loadedBuffersCount; size_t loadedBuffersLen; TYPE_1__** loadedBuffers; } ;
struct TYPE_6__ {scalar_t__ isTemp; } ;
typedef  TYPE_1__ GISTNodeBuffer ;
typedef  TYPE_2__ GISTBuildBuffers ;

/* Variables and functions */
 scalar_t__ repalloc (TYPE_1__**,int) ; 

__attribute__((used)) static void
gistAddLoadedBuffer(GISTBuildBuffers *gfbb, GISTNodeBuffer *nodeBuffer)
{
	/* Never add a temporary buffer to the array */
	if (nodeBuffer->isTemp)
		return;

	/* Enlarge the array if needed */
	if (gfbb->loadedBuffersCount >= gfbb->loadedBuffersLen)
	{
		gfbb->loadedBuffersLen *= 2;
		gfbb->loadedBuffers = (GISTNodeBuffer **)
			repalloc(gfbb->loadedBuffers,
					 gfbb->loadedBuffersLen * sizeof(GISTNodeBuffer *));
	}

	gfbb->loadedBuffers[gfbb->loadedBuffersCount] = nodeBuffer;
	gfbb->loadedBuffersCount++;
}