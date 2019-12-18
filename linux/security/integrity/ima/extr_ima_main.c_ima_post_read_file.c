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
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum kernel_read_file_id { ____Placeholder_kernel_read_file_id } kernel_read_file_id ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;

/* Variables and functions */
 int EACCES ; 
 int FILE_CHECK ; 
 int IMA_APPRAISE_ENFORCE ; 
 int IMA_APPRAISE_FIRMWARE ; 
 int /*<<< orphan*/  MAY_READ ; 
 int READING_FIRMWARE ; 
 int READING_X509_CERTIFICATE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_cred () ; 
 int ima_appraise ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int process_measurement (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* read_idmap ; 
 int /*<<< orphan*/  security_task_getsecid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ima_post_read_file(struct file *file, void *buf, loff_t size,
		       enum kernel_read_file_id read_id)
{
	enum ima_hooks func;
	u32 secid;

	if (!file && read_id == READING_FIRMWARE) {
		if ((ima_appraise & IMA_APPRAISE_FIRMWARE) &&
		    (ima_appraise & IMA_APPRAISE_ENFORCE)) {
			pr_err("Prevent firmware loading_store.\n");
			return -EACCES;	/* INTEGRITY_UNKNOWN */
		}
		return 0;
	}

	/* permit signed certs */
	if (!file && read_id == READING_X509_CERTIFICATE)
		return 0;

	if (!file || !buf || size == 0) { /* should never happen */
		if (ima_appraise & IMA_APPRAISE_ENFORCE)
			return -EACCES;
		return 0;
	}

	func = read_idmap[read_id] ?: FILE_CHECK;
	security_task_getsecid(current, &secid);
	return process_measurement(file, current_cred(), secid, buf, size,
				   MAY_READ, func);
}