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
struct kern_ipc_perm {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kern_ipc_perm*) ; 
 int lsm_ipc_alloc (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  security_sem_free (struct kern_ipc_perm*) ; 
 int /*<<< orphan*/  sem_alloc_security ; 
 scalar_t__ unlikely (int) ; 

int security_sem_alloc(struct kern_ipc_perm *sma)
{
	int rc = lsm_ipc_alloc(sma);

	if (unlikely(rc))
		return rc;
	rc = call_int_hook(sem_alloc_security, 0, sma);
	if (unlikely(rc))
		security_sem_free(sma);
	return rc;
}