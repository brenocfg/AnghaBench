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
 int __add_metainfo (struct tcf_meta_ops const*,struct tcf_ife_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_metainfo_and_get_ops(const struct tcf_meta_ops *ops,
				    struct tcf_ife_info *ife, u32 metaid,
				    bool exists)
{
	int ret;

	if (!try_module_get(ops->owner))
		return -ENOENT;
	ret = __add_metainfo(ops, ife, metaid, NULL, 0, true, exists);
	if (ret)
		module_put(ops->owner);
	return ret;
}