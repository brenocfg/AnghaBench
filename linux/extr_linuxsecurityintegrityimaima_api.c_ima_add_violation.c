#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct integrity_iint_cache {int dummy; } ;
struct inode {int dummy; } ;
struct ima_template_entry {int dummy; } ;
struct ima_event_data {unsigned char const* member_2; char const* member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/ * member_3; struct file* member_1; struct integrity_iint_cache* member_0; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  violations; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_PCR ; 
 int /*<<< orphan*/  CONFIG_IMA_MEASURE_PCR_IDX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct inode* file_inode (struct file*) ; 
 int ima_alloc_init_template (struct ima_event_data*,struct ima_template_entry**) ; 
 int /*<<< orphan*/  ima_free_template_entry (struct ima_template_entry*) ; 
 TYPE_1__ ima_htable ; 
 int ima_store_template (struct ima_template_entry*,int,struct inode*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,unsigned char const*,char const*,char const*,int,int /*<<< orphan*/ ) ; 

void ima_add_violation(struct file *file, const unsigned char *filename,
		       struct integrity_iint_cache *iint,
		       const char *op, const char *cause)
{
	struct ima_template_entry *entry;
	struct inode *inode = file_inode(file);
	struct ima_event_data event_data = {iint, file, filename, NULL, 0,
					    cause};
	int violation = 1;
	int result;

	/* can overflow, only indicator */
	atomic_long_inc(&ima_htable.violations);

	result = ima_alloc_init_template(&event_data, &entry);
	if (result < 0) {
		result = -ENOMEM;
		goto err_out;
	}
	result = ima_store_template(entry, violation, inode,
				    filename, CONFIG_IMA_MEASURE_PCR_IDX);
	if (result < 0)
		ima_free_template_entry(entry);
err_out:
	integrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
			    op, cause, result, 0);
}