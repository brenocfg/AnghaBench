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
struct TYPE_3__ {int size_allocated; void* data; void* data_allocated; } ;
typedef  TYPE_1__ CString ;

/* Variables and functions */
 void* realloc (void*,int) ; 

__attribute__((used)) static void cstr_realloc(CString *cstr, int new_size)
{
	int size;
	void *data;

	size = cstr->size_allocated;
	if (size == 0) {
		size = 8;	/* no need to allocate a too small first string */
	}
	while (size < new_size)
		size = size * 2;
	data = realloc (cstr->data_allocated, size);
	cstr->data_allocated = data;
	cstr->size_allocated = size;
	cstr->data = data;
}