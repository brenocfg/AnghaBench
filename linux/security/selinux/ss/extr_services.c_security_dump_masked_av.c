#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct policydb {struct class_datum** class_val_to_struct; } ;
struct context {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;
struct common_datum {TYPE_1__ permissions; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct class_datum {TYPE_2__ permissions; struct common_datum* comdatum; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SELINUX_ERR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SYM_CLASSES ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char const*,char*,...) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ context_struct_to_string (struct policydb*,struct context*,char**,int*) ; 
 int /*<<< orphan*/  dump_masked_av_helper ; 
 scalar_t__ hashtab_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* sym_name (struct policydb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void security_dump_masked_av(struct policydb *policydb,
				    struct context *scontext,
				    struct context *tcontext,
				    u16 tclass,
				    u32 permissions,
				    const char *reason)
{
	struct common_datum *common_dat;
	struct class_datum *tclass_dat;
	struct audit_buffer *ab;
	char *tclass_name;
	char *scontext_name = NULL;
	char *tcontext_name = NULL;
	char *permission_names[32];
	int index;
	u32 length;
	bool need_comma = false;

	if (!permissions)
		return;

	tclass_name = sym_name(policydb, SYM_CLASSES, tclass - 1);
	tclass_dat = policydb->class_val_to_struct[tclass - 1];
	common_dat = tclass_dat->comdatum;

	/* init permission_names */
	if (common_dat &&
	    hashtab_map(common_dat->permissions.table,
			dump_masked_av_helper, permission_names) < 0)
		goto out;

	if (hashtab_map(tclass_dat->permissions.table,
			dump_masked_av_helper, permission_names) < 0)
		goto out;

	/* get scontext/tcontext in text form */
	if (context_struct_to_string(policydb, scontext,
				     &scontext_name, &length) < 0)
		goto out;

	if (context_struct_to_string(policydb, tcontext,
				     &tcontext_name, &length) < 0)
		goto out;

	/* audit a message */
	ab = audit_log_start(audit_context(),
			     GFP_ATOMIC, AUDIT_SELINUX_ERR);
	if (!ab)
		goto out;

	audit_log_format(ab, "op=security_compute_av reason=%s "
			 "scontext=%s tcontext=%s tclass=%s perms=",
			 reason, scontext_name, tcontext_name, tclass_name);

	for (index = 0; index < 32; index++) {
		u32 mask = (1 << index);

		if ((mask & permissions) == 0)
			continue;

		audit_log_format(ab, "%s%s",
				 need_comma ? "," : "",
				 permission_names[index]
				 ? permission_names[index] : "????");
		need_comma = true;
	}
	audit_log_end(ab);
out:
	/* release scontext/tcontext */
	kfree(tcontext_name);
	kfree(scontext_name);

	return;
}