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
struct TYPE_2__ {int /*<<< orphan*/  post_handler; int /*<<< orphan*/  pre_handler; int /*<<< orphan*/  symbol_name; } ;
struct fei_attr {int /*<<< orphan*/  list; int /*<<< orphan*/  retval; TYPE_1__ kp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adjust_error_retval (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fei_kprobe_handler ; 
 int /*<<< orphan*/  fei_post_handler ; 
 int /*<<< orphan*/  kfree (struct fei_attr*) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct fei_attr* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fei_attr *fei_attr_new(const char *sym, unsigned long addr)
{
	struct fei_attr *attr;

	attr = kzalloc(sizeof(*attr), GFP_KERNEL);
	if (attr) {
		attr->kp.symbol_name = kstrdup(sym, GFP_KERNEL);
		if (!attr->kp.symbol_name) {
			kfree(attr);
			return NULL;
		}
		attr->kp.pre_handler = fei_kprobe_handler;
		attr->kp.post_handler = fei_post_handler;
		attr->retval = adjust_error_retval(addr, 0);
		INIT_LIST_HEAD(&attr->list);
	}
	return attr;
}