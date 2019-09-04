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
struct ceph_pagelist_cursor {int /*<<< orphan*/  room; int /*<<< orphan*/  page_lru; struct ceph_pagelist* pl; } ;
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;
struct ceph_pagelist {int /*<<< orphan*/  room; TYPE_1__ head; } ;

/* Variables and functions */

void ceph_pagelist_set_cursor(struct ceph_pagelist *pl,
			      struct ceph_pagelist_cursor *c)
{
	c->pl = pl;
	c->page_lru = pl->head.prev;
	c->room = pl->room;
}