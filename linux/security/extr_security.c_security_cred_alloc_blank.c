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
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cred_alloc_blank ; 
 int lsm_cred_alloc (struct cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_cred_free (struct cred*) ; 
 scalar_t__ unlikely (int) ; 

int security_cred_alloc_blank(struct cred *cred, gfp_t gfp)
{
	int rc = lsm_cred_alloc(cred, gfp);

	if (rc)
		return rc;

	rc = call_int_hook(cred_alloc_blank, 0, cred, gfp);
	if (unlikely(rc))
		security_cred_free(cred);
	return rc;
}