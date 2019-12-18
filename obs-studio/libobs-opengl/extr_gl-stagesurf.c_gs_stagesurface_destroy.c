#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pack_buffer; } ;
typedef  TYPE_1__ gs_stagesurf_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  gl_delete_buffers (int,scalar_t__*) ; 

void gs_stagesurface_destroy(gs_stagesurf_t *stagesurf)
{
	if (stagesurf) {
		if (stagesurf->pack_buffer)
			gl_delete_buffers(1, &stagesurf->pack_buffer);

		bfree(stagesurf);
	}
}