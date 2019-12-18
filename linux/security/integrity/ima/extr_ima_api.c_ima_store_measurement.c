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
struct integrity_iint_cache {int measured_pcrs; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct ima_template_entry {int dummy; } ;
struct ima_template_desc {int dummy; } ;
struct ima_event_data {unsigned char const* filename; int xattr_len; struct modsig const* modsig; struct evm_ima_xattr_data* xattr_value; struct file* file; struct integrity_iint_cache* iint; } ;
struct file {int f_flags; } ;
struct evm_ima_xattr_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_PCR ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IMA_MEASURED ; 
 int O_DIRECT ; 
 struct inode* file_inode (struct file*) ; 
 int ima_alloc_init_template (struct ima_event_data*,struct ima_template_entry**,struct ima_template_desc*) ; 
 int /*<<< orphan*/  ima_free_template_entry (struct ima_template_entry*) ; 
 int ima_store_template (struct ima_template_entry*,int,struct inode*,unsigned char const*,int) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,unsigned char const*,char const*,char const*,int,int /*<<< orphan*/ ) ; 

void ima_store_measurement(struct integrity_iint_cache *iint,
			   struct file *file, const unsigned char *filename,
			   struct evm_ima_xattr_data *xattr_value,
			   int xattr_len, const struct modsig *modsig, int pcr,
			   struct ima_template_desc *template_desc)
{
	static const char op[] = "add_template_measure";
	static const char audit_cause[] = "ENOMEM";
	int result = -ENOMEM;
	struct inode *inode = file_inode(file);
	struct ima_template_entry *entry;
	struct ima_event_data event_data = { .iint = iint,
					     .file = file,
					     .filename = filename,
					     .xattr_value = xattr_value,
					     .xattr_len = xattr_len,
					     .modsig = modsig };
	int violation = 0;

	/*
	 * We still need to store the measurement in the case of MODSIG because
	 * we only have its contents to put in the list at the time of
	 * appraisal, but a file measurement from earlier might already exist in
	 * the measurement list.
	 */
	if (iint->measured_pcrs & (0x1 << pcr) && !modsig)
		return;

	result = ima_alloc_init_template(&event_data, &entry, template_desc);
	if (result < 0) {
		integrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
				    op, audit_cause, result, 0);
		return;
	}

	result = ima_store_template(entry, violation, inode, filename, pcr);
	if ((!result || result == -EEXIST) && !(file->f_flags & O_DIRECT)) {
		iint->flags |= IMA_MEASURED;
		iint->measured_pcrs |= (0x1 << pcr);
	}
	if (result < 0)
		ima_free_template_entry(entry);
}