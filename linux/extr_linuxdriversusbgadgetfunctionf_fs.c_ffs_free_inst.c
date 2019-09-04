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
struct usb_function_instance {int dummy; } ;
struct f_fs_opts {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ffs_free_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_dev_lock () ; 
 int /*<<< orphan*/  ffs_dev_unlock () ; 
 int /*<<< orphan*/  kfree (struct f_fs_opts*) ; 
 struct f_fs_opts* to_f_fs_opts (struct usb_function_instance*) ; 

__attribute__((used)) static void ffs_free_inst(struct usb_function_instance *f)
{
	struct f_fs_opts *opts;

	opts = to_f_fs_opts(f);
	ffs_dev_lock();
	_ffs_free_dev(opts->dev);
	ffs_dev_unlock();
	kfree(opts);
}