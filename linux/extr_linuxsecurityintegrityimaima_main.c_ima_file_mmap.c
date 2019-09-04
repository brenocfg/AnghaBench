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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  MMAP_CHECK ; 
 unsigned long PROT_EXEC ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_cred () ; 
 int process_measurement (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ima_file_mmap(struct file *file, unsigned long prot)
{
	u32 secid;

	if (file && (prot & PROT_EXEC)) {
		security_task_getsecid(current, &secid);
		return process_measurement(file, current_cred(), secid, NULL,
					   0, MAY_EXEC, MMAP_CHECK);
	}

	return 0;
}