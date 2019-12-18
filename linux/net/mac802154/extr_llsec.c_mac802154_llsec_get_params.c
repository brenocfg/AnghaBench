#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ieee802154_llsec_params {int dummy; } ;
struct mac802154_llsec {int /*<<< orphan*/  lock; struct ieee802154_llsec_params params; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

int mac802154_llsec_get_params(struct mac802154_llsec *sec,
			       struct ieee802154_llsec_params *params)
{
	read_lock_bh(&sec->lock);
	*params = sec->params;
	read_unlock_bh(&sec->lock);

	return 0;
}