#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int attrslen; TYPE_1__* attrs; int /*<<< orphan*/  color; } ;
struct TYPE_4__ {int loc; char const* a; } ;
typedef  TYPE_2__ RConsCanvas ;

/* Variables and functions */

__attribute__((used)) static const char **attr_at(RConsCanvas *c, int loc) {
	int i, j, delta;
	if (!c->color || c->attrslen == 0) {
		return NULL;
	}
	j = c->attrslen / 2;
	delta = c->attrslen / 2;
	for (i = 0; i < (c->attrslen); i++) {
		delta /= 2;
		if (delta == 0) {
			delta = 1;
		}
		if (c->attrs[j].loc == loc) {
			return &c->attrs[j].a;
		}
		if (c->attrs[j].loc < loc) {
			j += delta;
			if (j >= c->attrslen) {
				break;
			}
			if (c->attrs[j].loc > loc && delta == 1) {
				break;
			}
		} else if (c->attrs[j].loc > loc) {
			j -= delta;
			if (j <= 0) {
				break;
			}
			if (c->attrs[j].loc < loc && delta == 1) {
				break;
			}
		}
	}
	return NULL;
}