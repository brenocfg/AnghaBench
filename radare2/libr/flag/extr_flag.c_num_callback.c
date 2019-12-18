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
typedef  long long ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  ht_name; } ;
struct TYPE_4__ {long long offset; scalar_t__ alias; } ;
typedef  int /*<<< orphan*/  RNum ;
typedef  TYPE_1__ RFlagItem ;
typedef  TYPE_2__ RFlag ;

/* Variables and functions */
 TYPE_1__* ht_pp_find (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 num_callback(RNum *user, const char *name, int *ok) {
	RFlag *f = (RFlag *)user;
	if (ok) {
		*ok = 0;
	}
	RFlagItem *item = ht_pp_find (f->ht_name, name, NULL);
	if (item) {
		// NOTE: to avoid warning infinite loop here we avoid recursivity
		if (item->alias) {
			return 0LL;
		}
		if (ok) {
			*ok = 1;
		}
		return item->offset;
	}
	return 0LL;
}