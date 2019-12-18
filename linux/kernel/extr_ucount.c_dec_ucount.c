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
struct ucounts {int /*<<< orphan*/ * ucount; TYPE_1__* ns; } ;
typedef  enum ucount_type { ____Placeholder_ucount_type } ucount_type ;
struct TYPE_2__ {struct ucounts* ucounts; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ucounts (struct ucounts*) ; 

void dec_ucount(struct ucounts *ucounts, enum ucount_type type)
{
	struct ucounts *iter;
	for (iter = ucounts; iter; iter = iter->ns->ucounts) {
		int dec = atomic_dec_if_positive(&iter->ucount[type]);
		WARN_ON_ONCE(dec < 0);
	}
	put_ucounts(ucounts);
}