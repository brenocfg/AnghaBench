#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mcore_t ;
struct TYPE_3__ {scalar_t__ pos; scalar_t__ end; } ;
typedef  TYPE_1__ mcore_handle ;

/* Variables and functions */
 scalar_t__ MCORE_INSTR_ALIGN ; 
 int /*<<< orphan*/ * find_instruction (scalar_t__) ; 

mcore_t* mcore_next(mcore_handle* handle) {
	mcore_t *op = NULL;
	if (!handle || handle->pos + MCORE_INSTR_ALIGN > handle->end) {
		return NULL;
	}

	if (!op && handle->pos + 2 <= handle->end) {
		op = find_instruction (handle->pos);
	}
	handle->pos += MCORE_INSTR_ALIGN;
	
	return op;
}