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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_meta_ops {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENOENT ; 
 struct tcf_meta_ops* find_ife_oplist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ife_meta_id2name (int /*<<< orphan*/ ) ; 
 int ife_validate_metatype (struct tcf_meta_ops*,void*,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int load_metaops_and_vet(u32 metaid, void *val, int len, bool rtnl_held)
{
	struct tcf_meta_ops *ops = find_ife_oplist(metaid);
	int ret = 0;

	if (!ops) {
		ret = -ENOENT;
#ifdef CONFIG_MODULES
		if (rtnl_held)
			rtnl_unlock();
		request_module("ife-meta-%s", ife_meta_id2name(metaid));
		if (rtnl_held)
			rtnl_lock();
		ops = find_ife_oplist(metaid);
#endif
	}

	if (ops) {
		ret = 0;
		if (len)
			ret = ife_validate_metatype(ops, val, len);

		module_put(ops->owner);
	}

	return ret;
}