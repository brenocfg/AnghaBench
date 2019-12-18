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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  gs_indexbuffer_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* device_indexbuffer_create ) (int /*<<< orphan*/ ,int,void*,size_t,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;
typedef  enum gs_index_type { ____Placeholder_gs_index_type } gs_index_type ;

/* Variables and functions */
 int GS_DUP_BUFFER ; 
 int GS_UNSIGNED_SHORT ; 
 void* bmemdup (void*,size_t) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int,void*,size_t,int) ; 
 TYPE_2__* thread_graphics ; 

gs_indexbuffer_t *gs_indexbuffer_create(enum gs_index_type type, void *indices,
					size_t num, uint32_t flags)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_indexbuffer_create"))
		return NULL;

	if (indices && num && (flags & GS_DUP_BUFFER) != 0) {
		size_t size = type == GS_UNSIGNED_SHORT ? 2 : 4;
		indices = bmemdup(indices, size * num);
	}

	return graphics->exports.device_indexbuffer_create(
		graphics->device, type, indices, num, flags);
}