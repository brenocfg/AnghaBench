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
struct tcf_ife_info {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int __add_metainfo (struct tcf_meta_ops const*,struct tcf_ife_info*,int /*<<< orphan*/ ,void*,int,int,int) ; 
 struct tcf_meta_ops* find_ife_oplist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_metainfo(struct tcf_ife_info *ife, u32 metaid, void *metaval,
			int len, bool exists)
{
	const struct tcf_meta_ops *ops = find_ife_oplist(metaid);
	int ret;

	if (!ops)
		return -ENOENT;
	ret = __add_metainfo(ops, ife, metaid, metaval, len, false, exists);
	if (ret)
		/*put back what find_ife_oplist took */
		module_put(ops->owner);
	return ret;
}