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
typedef  int /*<<< orphan*/  u8 ;
struct inode {int dummy; } ;
struct ima_template_entry {int /*<<< orphan*/  pcr; int /*<<< orphan*/  digest; } ;
typedef  int /*<<< orphan*/  digest ;

/* Variables and functions */
 int AUDIT_CAUSE_LEN_MAX ; 
 int /*<<< orphan*/  AUDIT_INTEGRITY_PCR ; 
 int EEXIST ; 
 int TPM_DIGEST_SIZE ; 
 int ima_add_digest_entry (struct ima_template_entry*,int) ; 
 int /*<<< orphan*/  ima_extend_list_mutex ; 
 scalar_t__ ima_lookup_digest_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ima_pcr_extend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,struct inode*,unsigned char const*,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int ima_add_template_entry(struct ima_template_entry *entry, int violation,
			   const char *op, struct inode *inode,
			   const unsigned char *filename)
{
	u8 digest[TPM_DIGEST_SIZE];
	const char *audit_cause = "hash_added";
	char tpm_audit_cause[AUDIT_CAUSE_LEN_MAX];
	int audit_info = 1;
	int result = 0, tpmresult = 0;

	mutex_lock(&ima_extend_list_mutex);
	if (!violation) {
		memcpy(digest, entry->digest, sizeof(digest));
		if (ima_lookup_digest_entry(digest, entry->pcr)) {
			audit_cause = "hash_exists";
			result = -EEXIST;
			goto out;
		}
	}

	result = ima_add_digest_entry(entry, 1);
	if (result < 0) {
		audit_cause = "ENOMEM";
		audit_info = 0;
		goto out;
	}

	if (violation)		/* invalidate pcr */
		memset(digest, 0xff, sizeof(digest));

	tpmresult = ima_pcr_extend(digest, entry->pcr);
	if (tpmresult != 0) {
		snprintf(tpm_audit_cause, AUDIT_CAUSE_LEN_MAX, "TPM_error(%d)",
			 tpmresult);
		audit_cause = tpm_audit_cause;
		audit_info = 0;
	}
out:
	mutex_unlock(&ima_extend_list_mutex);
	integrity_audit_msg(AUDIT_INTEGRITY_PCR, inode, filename,
			    op, audit_cause, result, audit_info);
	return result;
}