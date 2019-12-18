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
typedef  int /*<<< orphan*/  on_dsm_detach_callback ;
struct TYPE_5__ {int /*<<< orphan*/  node; int /*<<< orphan*/  arg; int /*<<< orphan*/  function; } ;
typedef  TYPE_1__ dsm_segment_detach_callback ;
struct TYPE_6__ {int /*<<< orphan*/  on_detach; } ;
typedef  TYPE_2__ dsm_segment ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 TYPE_1__* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  slist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
on_dsm_detach(dsm_segment *seg, on_dsm_detach_callback function, Datum arg)
{
	dsm_segment_detach_callback *cb;

	cb = MemoryContextAlloc(TopMemoryContext,
							sizeof(dsm_segment_detach_callback));
	cb->function = function;
	cb->arg = arg;
	slist_push_head(&seg->on_detach, &cb->node);
}