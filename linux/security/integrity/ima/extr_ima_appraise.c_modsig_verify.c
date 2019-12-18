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
struct modsig {int dummy; } ;
typedef  enum integrity_status { ____Placeholder_integrity_status } integrity_status ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INTEGRITY_PLATFORM_KEYRING ; 
 int INTEGRITY_FAIL ; 
 int /*<<< orphan*/  INTEGRITY_KEYRING_IMA ; 
 int /*<<< orphan*/  INTEGRITY_KEYRING_PLATFORM ; 
 int INTEGRITY_PASS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int KEXEC_KERNEL_CHECK ; 
 int integrity_modsig_verify (int /*<<< orphan*/ ,struct modsig const*) ; 

__attribute__((used)) static int modsig_verify(enum ima_hooks func, const struct modsig *modsig,
			 enum integrity_status *status, const char **cause)
{
	int rc;

	rc = integrity_modsig_verify(INTEGRITY_KEYRING_IMA, modsig);
	if (IS_ENABLED(CONFIG_INTEGRITY_PLATFORM_KEYRING) && rc &&
	    func == KEXEC_KERNEL_CHECK)
		rc = integrity_modsig_verify(INTEGRITY_KEYRING_PLATFORM,
					     modsig);
	if (rc) {
		*cause = "invalid-signature";
		*status = INTEGRITY_FAIL;
	} else {
		*status = INTEGRITY_PASS;
	}

	return rc;
}