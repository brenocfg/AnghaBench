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
struct msrl_action {int /*<<< orphan*/  set_mask; int /*<<< orphan*/  clear_mask; int /*<<< orphan*/  msr_no; int /*<<< orphan*/  err; } ;

/* Variables and functions */
 int /*<<< orphan*/  msrl_update_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msrl_update_func(void *info)
{
	struct msrl_action *ma = info;

	ma->err = msrl_update_safe(ma->msr_no, ma->clear_mask, ma->set_mask);
}