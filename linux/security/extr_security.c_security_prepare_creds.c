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
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,struct cred const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cred_prepare ; 
 int lsm_cred_alloc (struct cred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_cred_free (struct cred*) ; 
 scalar_t__ unlikely (int) ; 

int security_prepare_creds(struct cred *new, const struct cred *old, gfp_t gfp)
{
	int rc = lsm_cred_alloc(new, gfp);

	if (rc)
		return rc;

	rc = call_int_hook(cred_prepare, 0, new, old, gfp);
	if (unlikely(rc))
		security_cred_free(new);
	return rc;
}