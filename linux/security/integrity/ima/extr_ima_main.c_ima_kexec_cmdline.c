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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  process_buffer_measurement (void const*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ima_kexec_cmdline(const void *buf, int size)
{
	u32 secid;

	if (buf && size != 0) {
		security_task_getsecid(current, &secid);
		process_buffer_measurement(buf, size, "kexec-cmdline",
					   current_cred(), secid);
	}
}