#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* device; } ;
typedef  TYPE_2__ gs_samplerstate_t ;
struct TYPE_5__ {TYPE_2__** cur_samplers; } ;

/* Variables and functions */
 int GS_MAX_TEXTURES ; 
 int /*<<< orphan*/  samplerstate_release (TYPE_2__*) ; 

void gs_samplerstate_destroy(gs_samplerstate_t *samplerstate)
{
	if (!samplerstate)
		return;

	if (samplerstate->device)
		for (int i = 0; i < GS_MAX_TEXTURES; i++)
			if (samplerstate->device->cur_samplers[i] ==
			    samplerstate)
				samplerstate->device->cur_samplers[i] = NULL;

	samplerstate_release(samplerstate);
}