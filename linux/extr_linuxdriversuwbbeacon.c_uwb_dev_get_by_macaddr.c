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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct uwb_rc {TYPE_1__ uwb_beca; } ;
struct uwb_mac_addr {int dummy; } ;
struct uwb_dev {int dummy; } ;
struct uwb_beca_e {int /*<<< orphan*/  uwb_dev; } ;

/* Variables and functions */
 struct uwb_beca_e* __uwb_beca_find_bymac (struct uwb_rc*,struct uwb_mac_addr const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct uwb_dev* uwb_dev_try_get (struct uwb_rc*,int /*<<< orphan*/ ) ; 

struct uwb_dev *uwb_dev_get_by_macaddr(struct uwb_rc *rc,
				       const struct uwb_mac_addr *macaddr)
{
	struct uwb_dev *found = NULL;
	struct uwb_beca_e *bce;

	mutex_lock(&rc->uwb_beca.mutex);
	bce = __uwb_beca_find_bymac(rc, macaddr);
	if (bce)
		found = uwb_dev_try_get(rc, bce->uwb_dev);
	mutex_unlock(&rc->uwb_beca.mutex);

	return found;
}