#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct duplicate_flag_t {int /*<<< orphan*/  ret; int /*<<< orphan*/  word; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */
 TYPE_1__* r_flag_item_clone (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ r_str_glob (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool duplicate_flag(RFlagItem *flag, void *u) {
	struct duplicate_flag_t *user = (struct duplicate_flag_t *)u;
	/* filter per flag spaces */
	if (r_str_glob (flag->name, user->word)) {
		RFlagItem *cloned_item = r_flag_item_clone (flag);
		if (!cloned_item) {
			return false;
		}
		r_list_append (user->ret, cloned_item);
	}
	return true;
}