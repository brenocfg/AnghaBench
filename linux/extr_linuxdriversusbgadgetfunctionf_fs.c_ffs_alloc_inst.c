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
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  free_func_inst; int /*<<< orphan*/  set_inst_name; } ;
struct ffs_dev {struct f_fs_opts* opts; } ;
struct f_fs_opts {struct usb_function_instance func_inst; struct ffs_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_CAST (struct ffs_dev*) ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ffs_dev*) ; 
 struct ffs_dev* _ffs_alloc_dev () ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffs_dev_lock () ; 
 int /*<<< orphan*/  ffs_dev_unlock () ; 
 int /*<<< orphan*/  ffs_free_inst ; 
 int /*<<< orphan*/  ffs_func_type ; 
 int /*<<< orphan*/  ffs_set_inst_name ; 
 int /*<<< orphan*/  kfree (struct f_fs_opts*) ; 
 struct f_fs_opts* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_function_instance *ffs_alloc_inst(void)
{
	struct f_fs_opts *opts;
	struct ffs_dev *dev;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);

	opts->func_inst.set_inst_name = ffs_set_inst_name;
	opts->func_inst.free_func_inst = ffs_free_inst;
	ffs_dev_lock();
	dev = _ffs_alloc_dev();
	ffs_dev_unlock();
	if (IS_ERR(dev)) {
		kfree(opts);
		return ERR_CAST(dev);
	}
	opts->dev = dev;
	dev->opts = opts;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &ffs_func_type);
	return &opts->func_inst;
}