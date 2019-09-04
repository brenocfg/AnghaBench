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
struct tcf_exts {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */

__attribute__((used)) static int tc_exts_setup_cb_egdev_call(struct tcf_exts *exts,
				       enum tc_setup_type type,
				       void *type_data, bool err_stop)
{
	int ok_count = 0;
#ifdef CONFIG_NET_CLS_ACT
	const struct tc_action *a;
	struct net_device *dev;
	int i, ret;

	if (!tcf_exts_has_actions(exts))
		return 0;

	for (i = 0; i < exts->nr_actions; i++) {
		a = exts->actions[i];
		if (!a->ops->get_dev)
			continue;
		dev = a->ops->get_dev(a);
		if (!dev)
			continue;
		ret = tc_setup_cb_egdev_call(dev, type, type_data, err_stop);
		a->ops->put_dev(dev);
		if (ret < 0)
			return ret;
		ok_count += ret;
	}
#endif
	return ok_count;
}