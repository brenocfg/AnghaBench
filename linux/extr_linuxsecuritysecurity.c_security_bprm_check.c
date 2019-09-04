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
struct linux_binprm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bprm_check_security ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct linux_binprm*) ; 
 int ima_bprm_check (struct linux_binprm*) ; 

int security_bprm_check(struct linux_binprm *bprm)
{
	int ret;

	ret = call_int_hook(bprm_check_security, 0, bprm);
	if (ret)
		return ret;
	return ima_bprm_check(bprm);
}