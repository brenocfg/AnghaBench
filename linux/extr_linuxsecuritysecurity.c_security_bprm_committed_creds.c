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
 int /*<<< orphan*/  bprm_committed_creds ; 
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct linux_binprm*) ; 

void security_bprm_committed_creds(struct linux_binprm *bprm)
{
	call_void_hook(bprm_committed_creds, bprm);
}