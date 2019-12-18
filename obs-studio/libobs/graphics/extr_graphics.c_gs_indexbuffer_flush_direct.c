#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gs_indexbuffer_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* gs_indexbuffer_flush_direct ) (int /*<<< orphan*/ *,void const*) ;} ;
struct TYPE_4__ {TYPE_1__ exports; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p2 (char*,int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void const*) ; 
 TYPE_2__* thread_graphics ; 

void gs_indexbuffer_flush_direct(gs_indexbuffer_t *indexbuffer,
				 const void *data)
{
	if (!gs_valid_p2("gs_indexbuffer_flush_direct", indexbuffer, data))
		return;

	thread_graphics->exports.gs_indexbuffer_flush_direct(indexbuffer, data);
}