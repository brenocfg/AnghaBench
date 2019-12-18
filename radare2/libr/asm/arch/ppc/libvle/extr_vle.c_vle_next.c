#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ vle_t ;
struct TYPE_10__ {scalar_t__ pos; scalar_t__ end; int /*<<< orphan*/  inc; } ;
typedef  TYPE_2__ vle_handle ;

/* Variables and functions */
 scalar_t__ USE_INTERNAL_PPC (TYPE_2__*) ; 
 TYPE_1__* find_e (scalar_t__) ; 
 TYPE_1__* find_ppc (scalar_t__) ; 
 TYPE_1__* find_se (scalar_t__) ; 

vle_t* vle_next(vle_handle* handle) {
	vle_t *op = NULL;
	if (!handle || handle->pos + handle->inc >= handle->end) {
		return NULL;
	}
	handle->pos += handle->inc;
	// 'e-32' always before 'se-16'

	if (USE_INTERNAL_PPC (handle) && handle->pos + 4 <= handle->end) {
		op = find_ppc (handle->pos);
	}
	if (!op && handle->pos + 4 <= handle->end) {
		op = find_e (handle->pos);
	}
	if (!op && handle->pos + 2 <= handle->end) {
		op = find_se (handle->pos);
	}

	handle->inc = op ? op->size : 0;
	return op;
}