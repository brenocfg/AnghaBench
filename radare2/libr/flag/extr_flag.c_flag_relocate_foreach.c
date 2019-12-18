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
typedef  scalar_t__ ut64 ;
struct flag_relocate_t {scalar_t__ neg_mask; scalar_t__ off; scalar_t__ off_mask; scalar_t__ to; int /*<<< orphan*/  n; int /*<<< orphan*/  f; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */
 int /*<<< orphan*/  update_flag_item_offset (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int,int) ; 

__attribute__((used)) static bool flag_relocate_foreach(RFlagItem *fi, void *user) {
	struct flag_relocate_t *u = (struct flag_relocate_t *)user;
	ut64 fn = fi->offset & u->neg_mask;
	ut64 on = u->off & u->neg_mask;
	if (fn == on) {
		ut64 fm = fi->offset & u->off_mask;
		ut64 om = u->to & u->off_mask;
		update_flag_item_offset (u->f, fi, (u->to & u->neg_mask) + fm + om, false, false);
		u->n++;
	}
	return true;
}