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
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMSG_FREEZE ; 
 int /*<<< orphan*/  PMSG_RECOVER ; 
 int /*<<< orphan*/  PMSG_RESTORE ; 
 int /*<<< orphan*/  PMSG_THAW ; 
 int /*<<< orphan*/  TEST_DEVICES ; 
 int /*<<< orphan*/  TEST_FREEZER ; 
 int create_image (int) ; 
 int /*<<< orphan*/  dpm_complete (int /*<<< orphan*/ ) ; 
 int dpm_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_resume (int /*<<< orphan*/ ) ; 
 int dpm_suspend (int /*<<< orphan*/ ) ; 
 int freeze_kernel_threads () ; 
 int freezer_test_done ; 
 int hibernate_preallocate_memory () ; 
 scalar_t__ hibernation_test (int /*<<< orphan*/ ) ; 
 scalar_t__ in_suspend ; 
 int platform_begin (int) ; 
 int /*<<< orphan*/  platform_end (int) ; 
 int /*<<< orphan*/  platform_recover (int) ; 
 int /*<<< orphan*/  pm_restore_gfp_mask () ; 
 int /*<<< orphan*/  pm_restrict_gfp_mask () ; 
 int /*<<< orphan*/  pm_suspend_clear_flags () ; 
 int /*<<< orphan*/  resume_console () ; 
 int /*<<< orphan*/  suspend_console () ; 
 int /*<<< orphan*/  swsusp_free () ; 
 int /*<<< orphan*/  thaw_kernel_threads () ; 

int hibernation_snapshot(int platform_mode)
{
	pm_message_t msg;
	int error;

	pm_suspend_clear_flags();
	error = platform_begin(platform_mode);
	if (error)
		goto Close;

	/* Preallocate image memory before shutting down devices. */
	error = hibernate_preallocate_memory();
	if (error)
		goto Close;

	error = freeze_kernel_threads();
	if (error)
		goto Cleanup;

	if (hibernation_test(TEST_FREEZER)) {

		/*
		 * Indicate to the caller that we are returning due to a
		 * successful freezer test.
		 */
		freezer_test_done = true;
		goto Thaw;
	}

	error = dpm_prepare(PMSG_FREEZE);
	if (error) {
		dpm_complete(PMSG_RECOVER);
		goto Thaw;
	}

	suspend_console();
	pm_restrict_gfp_mask();

	error = dpm_suspend(PMSG_FREEZE);

	if (error || hibernation_test(TEST_DEVICES))
		platform_recover(platform_mode);
	else
		error = create_image(platform_mode);

	/*
	 * In the case that we call create_image() above, the control
	 * returns here (1) after the image has been created or the
	 * image creation has failed and (2) after a successful restore.
	 */

	/* We may need to release the preallocated image pages here. */
	if (error || !in_suspend)
		swsusp_free();

	msg = in_suspend ? (error ? PMSG_RECOVER : PMSG_THAW) : PMSG_RESTORE;
	dpm_resume(msg);

	if (error || !in_suspend)
		pm_restore_gfp_mask();

	resume_console();
	dpm_complete(msg);

 Close:
	platform_end(platform_mode);
	return error;

 Thaw:
	thaw_kernel_threads();
 Cleanup:
	swsusp_free();
	goto Close;
}