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
struct integrity_iint_cache {int measured_pcrs; int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;
struct ima_template_entry {int dummy; } ;
struct ima_event_data {unsigned char const* member_2; int member_4; int /*<<< orphan*/ * member_5; struct evm_ima_xattr_data* member_3; struct file* member_1; struct integrity_iint_cache* member_0; } ;
struct file {int f_flags; } ;
struct evm_ima_xattr_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_PCR ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IMA_MEASURED ; 
 int O_DIRECT ; 
 struct inode* file_inode (struct file*) ; 
 int ima_alloc_init_template (struct ima_event_data*,struct ima_template_entry**) ; 
 int /*<<< orphan*/  ima_free_template_entry (struct ima_template_entry*) ; 
 int ima_store_template (struct ima_template_entry*,int,struct inode*,unsigned char const*,int) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,unsigned char const*,char const*,char const*,int,int /*<<< orphan*/ ) ; 

void ima_store_measurement(struct integrity_iint_cache *iint,
			   struct file *file, const unsigned char *filename,
			   struct evm_ima_xattr_data *xattr_value,
			   int xattr_len, int pcr)
{
	static const char op[] = "add_template_measure";
	static const char audit_cause[] = "ENOMEM";
	int result = -ENOMEM;
	struct inode *inode = file_inode(file);
	struct ima_template_entry *entry;
	struct ima_event_data event_data = {iint, file, filename, xattr_value,
					    xattr_len, NULL};
	int violation = 0;

	if (iint->measured_pcrs & (0x1 << pcr))
		return;

	result = ima_alloc_init_template(&event_data, &entry);
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