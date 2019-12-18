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
struct tcf_meta_ops {int (* alloc ) (struct tcf_meta_info*,void*,int /*<<< orphan*/ ) ;} ;
struct tcf_meta_info {int /*<<< orphan*/  metalist; struct tcf_meta_ops const* ops; int /*<<< orphan*/  metaid; } ;
struct tcf_ife_info {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  metalist; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tcf_meta_info*) ; 
 struct tcf_meta_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct tcf_meta_info*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __add_metainfo(const struct tcf_meta_ops *ops,
			  struct tcf_ife_info *ife, u32 metaid, void *metaval,
			  int len, bool atomic, bool exists)
{
	struct tcf_meta_info *mi = NULL;
	int ret = 0;

	mi = kzalloc(sizeof(*mi), atomic ? GFP_ATOMIC : GFP_KERNEL);
	if (!mi)
		return -ENOMEM;

	mi->metaid = metaid;
	mi->ops = ops;
	if (len > 0) {
		ret = ops->alloc(mi, metaval, atomic ? GFP_ATOMIC : GFP_KERNEL);
		if (ret != 0) {
			kfree(mi);
			return ret;
		}
	}

	if (exists)
		spin_lock_bh(&ife->tcf_lock);
	list_add_tail(&mi->metalist, &ife->metalist);
	if (exists)
		spin_unlock_bh(&ife->tcf_lock);

	return ret;
}