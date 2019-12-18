#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ preserve_context; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  PMSG_FREEZE ; 
 int /*<<< orphan*/  PMSG_RESTORE ; 
 int /*<<< orphan*/  cpu_hotplug_enable () ; 
 int /*<<< orphan*/  dpm_resume_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_resume_start (int /*<<< orphan*/ ) ; 
 int dpm_suspend_end (int /*<<< orphan*/ ) ; 
 int dpm_suspend_start (int /*<<< orphan*/ ) ; 
 int freeze_processes () ; 
 int /*<<< orphan*/  kernel_restart_prepare (int /*<<< orphan*/ *) ; 
 TYPE_1__* kexec_image ; 
 int kexec_in_progress ; 
 int /*<<< orphan*/  kexec_mutex ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  lock_system_sleep () ; 
 int /*<<< orphan*/  machine_kexec (TYPE_1__*) ; 
 int /*<<< orphan*/  machine_shutdown () ; 
 int /*<<< orphan*/  migrate_to_reboot_cpu () ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_prepare_console () ; 
 int /*<<< orphan*/  pm_restore_console () ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  resume_console () ; 
 int /*<<< orphan*/  suspend_console () ; 
 int suspend_disable_secondary_cpus () ; 
 int /*<<< orphan*/  suspend_enable_secondary_cpus () ; 
 int /*<<< orphan*/  syscore_resume () ; 
 int syscore_suspend () ; 
 int /*<<< orphan*/  thaw_processes () ; 
 int /*<<< orphan*/  unlock_system_sleep () ; 

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
		error = suspend_disable_secondary_cpus();
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
		suspend_enable_secondary_cpus();
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