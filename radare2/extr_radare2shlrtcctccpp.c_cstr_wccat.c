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
typedef  int nwchar_t ;
struct TYPE_4__ {int size; int size_allocated; scalar_t__ data; } ;
typedef  TYPE_1__ CString ;

/* Variables and functions */
 int /*<<< orphan*/  cstr_realloc (TYPE_1__*,int) ; 

void cstr_wccat(CString *cstr, int ch)
{
	int size;
	size = cstr->size + sizeof(nwchar_t);
	if (size > cstr->size_allocated) {
		cstr_realloc (cstr, size);
	}
	*(nwchar_t *) (((unsigned char *) cstr->data) + size - sizeof(nwchar_t)) = ch;
	cstr->size = size;
}