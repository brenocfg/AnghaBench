#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int compressionLevel; int /*<<< orphan*/ * base; } ;
struct TYPE_5__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_2__ LZ4_streamHC_t ;

/* Variables and functions */

void LZ4_resetStreamHC(LZ4_streamHC_t *LZ4_streamHCPtr, int compressionLevel)
{
	LZ4_streamHCPtr->internal_donotuse.base = NULL;
	LZ4_streamHCPtr->internal_donotuse.compressionLevel = (unsigned int)compressionLevel;
}