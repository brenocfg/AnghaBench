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
struct type {TYPE_1__* name; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  content; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int type_index_compare(const void *_a, const void *_b)
{
	const struct type *const *a = _a, *const *b = _b;

	if ((*a)->name->size != (*b)->name->size)
		return (*a)->name->size - (*b)->name->size;
	else
		return memcmp((*a)->name->content, (*b)->name->content,
			      (*a)->name->size);
}