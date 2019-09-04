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
struct usb_function {char* name; int /*<<< orphan*/  free_func; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; int /*<<< orphan*/  req_match; int /*<<< orphan*/  setup; int /*<<< orphan*/  disable; int /*<<< orphan*/  set_alt; int /*<<< orphan*/  unbind; int /*<<< orphan*/  bind; } ;
struct ffs_function {struct usb_function function; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENTER () ; 
 struct usb_function* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ffs_free ; 
 int /*<<< orphan*/  ffs_func_bind ; 
 int /*<<< orphan*/  ffs_func_disable ; 
 int /*<<< orphan*/  ffs_func_req_match ; 
 int /*<<< orphan*/  ffs_func_resume ; 
 int /*<<< orphan*/  ffs_func_set_alt ; 
 int /*<<< orphan*/  ffs_func_setup ; 
 int /*<<< orphan*/  ffs_func_suspend ; 
 int /*<<< orphan*/  ffs_func_unbind ; 
 struct ffs_function* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct usb_function *ffs_alloc(struct usb_function_instance *fi)
{
	struct ffs_function *func;

	ENTER();

	func = kzalloc(sizeof(*func), GFP_KERNEL);
	if (unlikely(!func))
		return ERR_PTR(-ENOMEM);

	func->function.name    = "Function FS Gadget";

	func->function.bind    = ffs_func_bind;
	func->function.unbind  = ffs_func_unbind;
	func->function.set_alt = ffs_func_set_alt;
	func->function.disable = ffs_func_disable;
	func->function.setup   = ffs_func_setup;
	func->function.req_match = ffs_func_req_match;
	func->function.suspend = ffs_func_suspend;
	func->function.resume  = ffs_func_resume;
	func->function.free_func = ffs_free;

	return &func->function;
}