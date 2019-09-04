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
struct __stripe_pages_2d {unsigned int pages_in_unit; TYPE_1__* _1p_stripes; } ;
struct TYPE_2__ {struct __stripe_pages_2d* pages; scalar_t__ alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct __stripe_pages_2d*) ; 

__attribute__((used)) static void _sp2d_free(struct __stripe_pages_2d *sp2d)
{
	unsigned i;

	if (!sp2d)
		return;

	for (i = 0; i < sp2d->pages_in_unit; ++i) {
		if (sp2d->_1p_stripes[i].alloc)
			kfree(sp2d->_1p_stripes[i].pages);
	}

	kfree(sp2d);
}