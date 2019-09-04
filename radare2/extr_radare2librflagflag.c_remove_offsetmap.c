#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  by_off; } ;
struct TYPE_11__ {int /*<<< orphan*/  offset; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ RFlagsAtOffset ;
typedef  TYPE_2__ RFlagItem ;
typedef  TYPE_3__ RFlag ;

/* Variables and functions */
 TYPE_1__* r_flag_get_nearest_list (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_delete_data (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ r_list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_if_fail (int) ; 
 int /*<<< orphan*/  r_skiplist_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void remove_offsetmap(RFlag *f, RFlagItem *item) {
	r_return_if_fail (f && item);
	RFlagsAtOffset *flags = r_flag_get_nearest_list (f, item->offset, 0);
	if (flags) {
		r_list_delete_data (flags->flags, item);
		if (r_list_empty (flags->flags)) {
			r_skiplist_delete (f->by_off, flags);
		}
	}
}