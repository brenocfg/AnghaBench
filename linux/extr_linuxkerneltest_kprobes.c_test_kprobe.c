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

/* Variables and functions */
 int /*<<< orphan*/  handler_errors ; 
 int /*<<< orphan*/  kp ; 
 scalar_t__ posth_val ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ preh_val ; 
 int /*<<< orphan*/  rand1 ; 
 int register_kprobe (int /*<<< orphan*/ *) ; 
 int target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_kprobe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_kprobe(void)
{
	int ret;

	ret = register_kprobe(&kp);
	if (ret < 0) {
		pr_err("register_kprobe returned %d\n", ret);
		return ret;
	}

	ret = target(rand1);
	unregister_kprobe(&kp);

	if (preh_val == 0) {
		pr_err("kprobe pre_handler not called\n");
		handler_errors++;
	}

	if (posth_val == 0) {
		pr_err("kprobe post_handler not called\n");
		handler_errors++;
	}

	return 0;
}