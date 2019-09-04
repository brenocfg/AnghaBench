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
struct TYPE_2__ {scalar_t__ empty_lebs; } ;
struct ubifs_info {scalar_t__ main_lebs; int /*<<< orphan*/  lp_mutex; TYPE_1__ lst; } ;

/* Variables and functions */
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 

__attribute__((used)) static inline void ubifs_release_lprops(struct ubifs_info *c)
{
	ubifs_assert(c, mutex_is_locked(&c->lp_mutex));
	ubifs_assert(c, c->lst.empty_lebs >= 0 &&
		     c->lst.empty_lebs <= c->main_lebs);
	mutex_unlock(&c->lp_mutex);
}