#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_output_handle {TYPE_1__* rb; int /*<<< orphan*/  event; } ;
struct TYPE_2__ {void* aux_priv; } ;

/* Variables and functions */

void *perf_get_aux(struct perf_output_handle *handle)
{
	/* this is only valid between perf_aux_output_begin and *_end */
	if (!handle->event)
		return NULL;

	return handle->rb->aux_priv;
}