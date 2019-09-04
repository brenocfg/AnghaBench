#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ppp_net {int /*<<< orphan*/  all_ppp_mutex; int /*<<< orphan*/  units_idr; } ;
struct TYPE_3__ {int index; } ;
struct ppp {TYPE_1__ file; TYPE_2__* dev; int /*<<< orphan*/  ppp_net; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ppp_net* ppp_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_unit_count ; 
 int register_netdevice (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unit_find (int /*<<< orphan*/ *,int) ; 
 int unit_get (int /*<<< orphan*/ *,struct ppp*) ; 
 int /*<<< orphan*/  unit_put (int /*<<< orphan*/ *,int) ; 
 int unit_set (int /*<<< orphan*/ *,struct ppp*,int) ; 

__attribute__((used)) static int ppp_unit_register(struct ppp *ppp, int unit, bool ifname_is_set)
{
	struct ppp_net *pn = ppp_pernet(ppp->ppp_net);
	int ret;

	mutex_lock(&pn->all_ppp_mutex);

	if (unit < 0) {
		ret = unit_get(&pn->units_idr, ppp);
		if (ret < 0)
			goto err;
	} else {
		/* Caller asked for a specific unit number. Fail with -EEXIST
		 * if unavailable. For backward compatibility, return -EEXIST
		 * too if idr allocation fails; this makes pppd retry without
		 * requesting a specific unit number.
		 */
		if (unit_find(&pn->units_idr, unit)) {
			ret = -EEXIST;
			goto err;
		}
		ret = unit_set(&pn->units_idr, ppp, unit);
		if (ret < 0) {
			/* Rewrite error for backward compatibility */
			ret = -EEXIST;
			goto err;
		}
	}
	ppp->file.index = ret;

	if (!ifname_is_set)
		snprintf(ppp->dev->name, IFNAMSIZ, "ppp%i", ppp->file.index);

	mutex_unlock(&pn->all_ppp_mutex);

	ret = register_netdevice(ppp->dev);
	if (ret < 0)
		goto err_unit;

	atomic_inc(&ppp_unit_count);

	return 0;

err_unit:
	mutex_lock(&pn->all_ppp_mutex);
	unit_put(&pn->units_idr, ppp->file.index);
err:
	mutex_unlock(&pn->all_ppp_mutex);

	return ret;
}