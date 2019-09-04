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

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_hotplug_enable () ; 
 int /*<<< orphan*/  kernel_restart_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kexec_image ; 
 int kexec_in_progress ; 
 int /*<<< orphan*/  kexec_mutex ; 
 int /*<<< orphan*/  machine_kexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_shutdown () ; 
 int /*<<< orphan*/  migrate_to_reboot_cpu () ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

int kernel_kexec(void)
{
	int error = 0;

	if (!mutex_trylock(&kexec_mutex))
		return -EBUSY;
	if (!kexec_image) {
		error = -EINVAL;
		goto Unlock;
	}

#ifdef CONFIG_KEXEC_JUMP
	if (kexec_image->preserve_context) {
		lock_system_sleep();
		pm_prepare_console();
		error = freeze_processes();
		if (error) {
			error = -EBUSY;
			goto Restore_console;
		}
		suspend_console();
		error = dpm_suspend_start(PMSG_FREEZE);
		if (error)
			goto Resume_console;
		/* At this point, dpm_suspend_start() has been called,
		 * but *not* dpm_suspend_end(). We *must* call
		 * dpm_suspend_end() now.  Otherwise, drivers for
		 * some devices (e.g. interrupt controllers) become
		 * desynchronized with the actual state of the
		 * hardware at resume time, and evil weirdness ensues.
		 */
		error = dpm_suspend_end(PMSG_FREEZE);
		if (error)
			goto Resume_devices;
		error = disable_nonboot_cpus();
		if (error)
			goto Enable_cpus;
		local_irq_disable();
		error = syscore_suspend();
		if (error)
			goto Enable_irqs;
	} else
#endif
	{
		kexec_in_progress = true;
		kernel_restart_prepare(NULL);
		migrate_to_reboot_cpu();

		/*
		 * migrate_to_reboot_cpu() disables CPU hotplug assuming that
		 * no further code needs to use CPU hotplug (which is true in
		 * the reboot case). However, the kexec path depends on using
		 * CPU hotplug again; so re-enable it here.
		 */
		cpu_hotplug_enable();
		pr_emerg("Starting new kernel\n");
		machine_shutdown();
	}

	machine_kexec(kexec_image);

#ifdef CONFIG_KEXEC_JUMP
	if (kexec_image->preserve_context) {
		syscore_resume();
 Enable_irqs:
		local_irq_enable();
 Enable_cpus:
		enable_nonboot_cpus();
		dpm_resume_start(PMSG_RESTORE);
 Resume_devices:
		dpm_resume_end(PMSG_RESTORE);
 Resume_console:
		resume_console();
		thaw_processes();
 Restore_console:
		pm_restore_console();
		unlock_system_sleep();
	}
#endif

 Unlock:
	mutex_unlock(&kexec_mutex);
	return error;
}