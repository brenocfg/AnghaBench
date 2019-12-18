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
struct TYPE_3__ {int /*<<< orphan*/  attrs; scalar_t__ attr; int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ RConsCanvas ;

/* Variables and functions */
 int /*<<< orphan*/  ht_up_delete (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ht_up_update (int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static void __stampAttribute(RConsCanvas *c, int loc, int length) {
	if (!c->color) {
		return;
	}
	int i;
	ht_up_update (c->attrs, loc, (void *)c->attr);
	for (i = 1; i < length; i++) {
		ht_up_delete (c->attrs, loc + i);
	}
}