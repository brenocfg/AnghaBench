#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t num; scalar_t__ array; } ;
struct TYPE_5__ {TYPE_3__ procs; } ;
typedef  TYPE_1__ proc_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (TYPE_3__) ; 
 int /*<<< orphan*/  proc_info_free (scalar_t__) ; 

void proc_handler_destroy(proc_handler_t *handler)
{
	if (handler) {
		for (size_t i = 0; i < handler->procs.num; i++)
			proc_info_free(handler->procs.array + i);
		da_free(handler->procs);
		bfree(handler);
	}
}