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
struct cred {int /*<<< orphan*/ * security; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_void_hook (int /*<<< orphan*/ ,struct cred*) ; 
 int /*<<< orphan*/  cred_free ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void security_cred_free(struct cred *cred)
{
	/*
	 * There is a failure case in prepare_creds() that
	 * may result in a call here with ->security being NULL.
	 */
	if (unlikely(cred->security == NULL))
		return;

	call_void_hook(cred_free, cred);

	kfree(cred->security);
	cred->security = NULL;
}