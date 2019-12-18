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
struct integrity_iint_cache {int flags; TYPE_1__* ima_hash; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_2__ {size_t algo; int length; int /*<<< orphan*/ * digest; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_RULE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IMA_AUDITED ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_task_info (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,unsigned char const*) ; 
 char** hash_algo_name ; 
 int /*<<< orphan*/  hex_byte_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 

void ima_audit_measurement(struct integrity_iint_cache *iint,
			   const unsigned char *filename)
{
	struct audit_buffer *ab;
	char *hash;
	const char *algo_name = hash_algo_name[iint->ima_hash->algo];
	int i;

	if (iint->flags & IMA_AUDITED)
		return;

	hash = kzalloc((iint->ima_hash->length * 2) + 1, GFP_KERNEL);
	if (!hash)
		return;

	for (i = 0; i < iint->ima_hash->length; i++)
		hex_byte_pack(hash + (i * 2), iint->ima_hash->digest[i]);
	hash[i * 2] = '\0';

	ab = audit_log_start(audit_context(), GFP_KERNEL,
			     AUDIT_INTEGRITY_RULE);
	if (!ab)
		goto out;

	audit_log_format(ab, "file=");
	audit_log_untrustedstring(ab, filename);
	audit_log_format(ab, " hash=\"%s:%s\"", algo_name, hash);

	audit_log_task_info(ab);
	audit_log_end(ab);

	iint->flags |= IMA_AUDITED;
out:
	kfree(hash);
	return;
}