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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {char const* name; } ;
typedef  int /*<<< orphan*/  RNum ;
typedef  int /*<<< orphan*/  RList ;
typedef  TYPE_1__ RFlagItem ;
typedef  int /*<<< orphan*/  RFlag ;

/* Variables and functions */
 int /*<<< orphan*/ * r_flag_get_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_list_get_top (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const char *str_callback(RNum *user, ut64 off, int *ok) {
	RFlag *f = (RFlag*)user;
	if (ok) {
		*ok = 0;
	}
	if (f) {
		const RList *list = r_flag_get_list (f, off);
		RFlagItem *item = r_list_get_top (list);
		if (item) {
			if (ok) {
				*ok = true;
			}
			return item->name;
		}
	}
	return NULL;
}