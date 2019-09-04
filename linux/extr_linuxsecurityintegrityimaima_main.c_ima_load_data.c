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
typedef  enum kernel_load_data_id { ____Placeholder_kernel_load_data_id } kernel_load_data_id ;

/* Variables and functions */
 int EACCES ; 
 int IMA_APPRAISE_ENFORCE ; 
 int IMA_APPRAISE_FIRMWARE ; 
 int IMA_APPRAISE_KEXEC ; 
 int IMA_APPRAISE_MODULES ; 
#define  LOADING_FIRMWARE 130 
#define  LOADING_KEXEC_IMAGE 129 
#define  LOADING_MODULE 128 
 int ima_appraise ; 
 int is_module_sig_enforced () ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int ima_load_data(enum kernel_load_data_id id)
{
	bool sig_enforce;

	if ((ima_appraise & IMA_APPRAISE_ENFORCE) != IMA_APPRAISE_ENFORCE)
		return 0;

	switch (id) {
	case LOADING_KEXEC_IMAGE:
		if (ima_appraise & IMA_APPRAISE_KEXEC) {
			pr_err("impossible to appraise a kernel image without a file descriptor; try using kexec_file_load syscall.\n");
			return -EACCES;	/* INTEGRITY_UNKNOWN */
		}
		break;
	case LOADING_FIRMWARE:
		if (ima_appraise & IMA_APPRAISE_FIRMWARE) {
			pr_err("Prevent firmware sysfs fallback loading.\n");
			return -EACCES;	/* INTEGRITY_UNKNOWN */
		}
		break;
	case LOADING_MODULE:
		sig_enforce = is_module_sig_enforced();

		if (!sig_enforce && (ima_appraise & IMA_APPRAISE_MODULES)) {
			pr_err("impossible to appraise a module without a file descriptor. sig_enforce kernel parameter might help\n");
			return -EACCES;	/* INTEGRITY_UNKNOWN */
		}
	default:
		break;
	}
	return 0;
}