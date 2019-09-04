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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  MCDI_DECLARE_BUF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCDI_SET_DWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_CMD_REBOOT ; 
 int /*<<< orphan*/  MC_CMD_REBOOT_FLAGS_AFTER_ASSERTION ; 
 int /*<<< orphan*/  MC_CMD_REBOOT_IN_LEN ; 
 scalar_t__ MC_CMD_REBOOT_OUT_LEN ; 
 int /*<<< orphan*/  REBOOT_IN_FLAGS ; 
 int /*<<< orphan*/  efx_mcdi_display_error (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int efx_mcdi_rpc_quiet (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inbuf ; 

__attribute__((used)) static int efx_mcdi_exit_assertion(struct efx_nic *efx)
{
	MCDI_DECLARE_BUF(inbuf, MC_CMD_REBOOT_IN_LEN);
	int rc;

	/* If the MC is running debug firmware, it might now be
	 * waiting for a debugger to attach, but we just want it to
	 * reboot.  We set a flag that makes the command a no-op if it
	 * has already done so.
	 * The MCDI will thus return either 0 or -EIO.
	 */
	BUILD_BUG_ON(MC_CMD_REBOOT_OUT_LEN != 0);
	MCDI_SET_DWORD(inbuf, REBOOT_IN_FLAGS,
		       MC_CMD_REBOOT_FLAGS_AFTER_ASSERTION);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_REBOOT, inbuf, MC_CMD_REBOOT_IN_LEN,
				NULL, 0, NULL);
	if (rc == -EIO)
		rc = 0;
	if (rc)
		efx_mcdi_display_error(efx, MC_CMD_REBOOT, MC_CMD_REBOOT_IN_LEN,
				       NULL, 0, rc);
	return rc;
}