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
struct kprobe {scalar_t__ flags; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  handler_errors ; 
 struct kprobe kp ; 
 struct kprobe kp2 ; 
 scalar_t__ posth_val ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ preh_val ; 
 int /*<<< orphan*/  rand1 ; 
 int register_kprobes (struct kprobe**,int) ; 
 int target (int /*<<< orphan*/ ) ; 
 int target2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_kprobes (struct kprobe**,int) ; 

__attribute__((used)) static int test_kprobes(void)
{
	int ret;
	struct kprobe *kps[2] = {&kp, &kp2};

	/* addr and flags should be cleard for reusing kprobe. */
	kp.addr = NULL;
	kp.flags = 0;
	ret = register_kprobes(kps, 2);
	if (ret < 0) {
		pr_err("register_kprobes returned %d\n", ret);
		return ret;
	}

	preh_val = 0;
	posth_val = 0;
	ret = target(rand1);

	if (preh_val == 0) {
		pr_err("kprobe pre_handler not called\n");
		handler_errors++;
	}

	if (posth_val == 0) {
		pr_err("kprobe post_handler not called\n");
		handler_errors++;
	}

	preh_val = 0;
	posth_val = 0;
	ret = target2(rand1);

	if (preh_val == 0) {
		pr_err("kprobe pre_handler2 not called\n");
		handler_errors++;
	}

	if (posth_val == 0) {
		pr_err("kprobe post_handler2 not called\n");
		handler_errors++;
	}

	unregister_kprobes(kps, 2);
	return 0;

}