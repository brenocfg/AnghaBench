#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uid_t ;
struct TYPE_4__ {char* from; } ;
typedef  TYPE_1__ substring_t ;
struct ima_template_desc {int /*<<< orphan*/  num_fields; int /*<<< orphan*/  fields; int /*<<< orphan*/  fmt; } ;
struct ima_rule_entry {scalar_t__ action; int flags; unsigned long fsmagic; struct ima_template_desc* template; void* func; int /*<<< orphan*/  pcr; void* fowner; int /*<<< orphan*/ * fowner_op; void* uid; int /*<<< orphan*/ * uid_op; int /*<<< orphan*/  fsuuid; int /*<<< orphan*/  fsname; int /*<<< orphan*/  mask; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ APPRAISE ; 
 scalar_t__ AUDIT ; 
 int /*<<< orphan*/  AUDIT_INTEGRITY_POLICY_RULE ; 
 int /*<<< orphan*/  AUDIT_OBJ_ROLE ; 
 int /*<<< orphan*/  AUDIT_OBJ_TYPE ; 
 int /*<<< orphan*/  AUDIT_OBJ_USER ; 
 int /*<<< orphan*/  AUDIT_SUBJ_ROLE ; 
 int /*<<< orphan*/  AUDIT_SUBJ_TYPE ; 
 int /*<<< orphan*/  AUDIT_SUBJ_USER ; 
 void* BPRM_CHECK ; 
 void* CREDS_CHECK ; 
 scalar_t__ DONT_APPRAISE ; 
 scalar_t__ DONT_HASH ; 
 scalar_t__ DONT_MEASURE ; 
 int EINVAL ; 
 int ENOMEM ; 
 void* FILE_CHECK ; 
 void* FIRMWARE_CHECK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HASH ; 
 int IMA_DIGSIG_REQUIRED ; 
 int IMA_EUID ; 
 int IMA_FOWNER ; 
 int IMA_FSMAGIC ; 
 int IMA_FSNAME ; 
 int IMA_FSUUID ; 
 int IMA_FUNC ; 
 int IMA_INMASK ; 
 int IMA_MASK ; 
 int IMA_MODSIG_ALLOWED ; 
 int IMA_PCR ; 
 int IMA_PERMIT_DIRECTIO ; 
 int IMA_UID ; 
 int /*<<< orphan*/  INVALID_PCR (int /*<<< orphan*/ ) ; 
 void* INVALID_UID ; 
 void* KEXEC_CMDLINE ; 
 void* KEXEC_INITRAMFS_CHECK ; 
 void* KEXEC_KERNEL_CHECK ; 
 int /*<<< orphan*/  LSM_OBJ_ROLE ; 
 int /*<<< orphan*/  LSM_OBJ_TYPE ; 
 int /*<<< orphan*/  LSM_OBJ_USER ; 
 int /*<<< orphan*/  LSM_SUBJ_ROLE ; 
 int /*<<< orphan*/  LSM_SUBJ_TYPE ; 
 int /*<<< orphan*/  LSM_SUBJ_USER ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  MAY_APPEND ; 
 int /*<<< orphan*/  MAY_EXEC ; 
 int /*<<< orphan*/  MAY_READ ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 scalar_t__ MEASURE ; 
 void* MMAP_CHECK ; 
 void* MODULE_CHECK ; 
#define  Opt_appraise 159 
#define  Opt_appraise_type 158 
#define  Opt_audit 157 
#define  Opt_dont_appraise 156 
#define  Opt_dont_hash 155 
#define  Opt_dont_measure 154 
#define  Opt_err 153 
#define  Opt_euid_eq 152 
#define  Opt_euid_gt 151 
#define  Opt_euid_lt 150 
#define  Opt_fowner_eq 149 
#define  Opt_fowner_gt 148 
#define  Opt_fowner_lt 147 
#define  Opt_fsmagic 146 
#define  Opt_fsname 145 
#define  Opt_fsuuid 144 
#define  Opt_func 143 
#define  Opt_hash 142 
#define  Opt_mask 141 
#define  Opt_measure 140 
#define  Opt_obj_role 139 
#define  Opt_obj_type 138 
#define  Opt_obj_user 137 
#define  Opt_pcr 136 
#define  Opt_permit_directio 135 
#define  Opt_subj_role 134 
#define  Opt_subj_type 133 
#define  Opt_subj_user 132 
#define  Opt_template 131 
#define  Opt_uid_eq 130 
#define  Opt_uid_gt 129 
#define  Opt_uid_lt 128 
 void* POLICY_CHECK ; 
 scalar_t__ UNKNOWN ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int) ; 
 int /*<<< orphan*/  check_template_modsig (struct ima_template_desc*) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  ima_appraise_flag (void*) ; 
 int /*<<< orphan*/  ima_hook_supports_modsig (void*) ; 
 int /*<<< orphan*/  ima_log_string (struct audit_buffer*,char*,char*) ; 
 int /*<<< orphan*/  ima_log_string_op (struct audit_buffer*,char*,char*,int /*<<< orphan*/ *) ; 
 int ima_lsm_rule_init (struct ima_rule_entry*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ima_template_desc* ima_template_desc_current () ; 
 struct audit_buffer* integrity_audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int kstrtoint (char*,int,int /*<<< orphan*/ *) ; 
 int kstrtoul (char*,int,unsigned long*) ; 
 struct ima_template_desc* lookup_template_desc (char*) ; 
 void* make_kuid (int /*<<< orphan*/ ,unsigned long) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  policy_tokens ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  temp_ima_appraise ; 
 int /*<<< orphan*/  template_desc_init_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid_eq ; 
 int /*<<< orphan*/  uid_gt ; 
 int /*<<< orphan*/  uid_lt ; 
 int /*<<< orphan*/  uid_valid (void*) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ *) ; 
 int uuid_parse (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ima_parse_rule(char *rule, struct ima_rule_entry *entry)
{
	struct audit_buffer *ab;
	char *from;
	char *p;
	bool uid_token;
	struct ima_template_desc *template_desc;
	int result = 0;

	ab = integrity_audit_log_start(audit_context(), GFP_KERNEL,
				       AUDIT_INTEGRITY_POLICY_RULE);

	entry->uid = INVALID_UID;
	entry->fowner = INVALID_UID;
	entry->uid_op = &uid_eq;
	entry->fowner_op = &uid_eq;
	entry->action = UNKNOWN;
	while ((p = strsep(&rule, " \t")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		unsigned long lnum;

		if (result < 0)
			break;
		if ((*p == '\0') || (*p == ' ') || (*p == '\t'))
			continue;
		token = match_token(p, policy_tokens, args);
		switch (token) {
		case Opt_measure:
			ima_log_string(ab, "action", "measure");

			if (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = MEASURE;
			break;
		case Opt_dont_measure:
			ima_log_string(ab, "action", "dont_measure");

			if (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = DONT_MEASURE;
			break;
		case Opt_appraise:
			ima_log_string(ab, "action", "appraise");

			if (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = APPRAISE;
			break;
		case Opt_dont_appraise:
			ima_log_string(ab, "action", "dont_appraise");

			if (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = DONT_APPRAISE;
			break;
		case Opt_audit:
			ima_log_string(ab, "action", "audit");

			if (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = AUDIT;
			break;
		case Opt_hash:
			ima_log_string(ab, "action", "hash");

			if (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = HASH;
			break;
		case Opt_dont_hash:
			ima_log_string(ab, "action", "dont_hash");

			if (entry->action != UNKNOWN)
				result = -EINVAL;

			entry->action = DONT_HASH;
			break;
		case Opt_func:
			ima_log_string(ab, "func", args[0].from);

			if (entry->func)
				result = -EINVAL;

			if (strcmp(args[0].from, "FILE_CHECK") == 0)
				entry->func = FILE_CHECK;
			/* PATH_CHECK is for backwards compat */
			else if (strcmp(args[0].from, "PATH_CHECK") == 0)
				entry->func = FILE_CHECK;
			else if (strcmp(args[0].from, "MODULE_CHECK") == 0)
				entry->func = MODULE_CHECK;
			else if (strcmp(args[0].from, "FIRMWARE_CHECK") == 0)
				entry->func = FIRMWARE_CHECK;
			else if ((strcmp(args[0].from, "FILE_MMAP") == 0)
				|| (strcmp(args[0].from, "MMAP_CHECK") == 0))
				entry->func = MMAP_CHECK;
			else if (strcmp(args[0].from, "BPRM_CHECK") == 0)
				entry->func = BPRM_CHECK;
			else if (strcmp(args[0].from, "CREDS_CHECK") == 0)
				entry->func = CREDS_CHECK;
			else if (strcmp(args[0].from, "KEXEC_KERNEL_CHECK") ==
				 0)
				entry->func = KEXEC_KERNEL_CHECK;
			else if (strcmp(args[0].from, "KEXEC_INITRAMFS_CHECK")
				 == 0)
				entry->func = KEXEC_INITRAMFS_CHECK;
			else if (strcmp(args[0].from, "POLICY_CHECK") == 0)
				entry->func = POLICY_CHECK;
			else if (strcmp(args[0].from, "KEXEC_CMDLINE") == 0)
				entry->func = KEXEC_CMDLINE;
			else
				result = -EINVAL;
			if (!result)
				entry->flags |= IMA_FUNC;
			break;
		case Opt_mask:
			ima_log_string(ab, "mask", args[0].from);

			if (entry->mask)
				result = -EINVAL;

			from = args[0].from;
			if (*from == '^')
				from++;

			if ((strcmp(from, "MAY_EXEC")) == 0)
				entry->mask = MAY_EXEC;
			else if (strcmp(from, "MAY_WRITE") == 0)
				entry->mask = MAY_WRITE;
			else if (strcmp(from, "MAY_READ") == 0)
				entry->mask = MAY_READ;
			else if (strcmp(from, "MAY_APPEND") == 0)
				entry->mask = MAY_APPEND;
			else
				result = -EINVAL;
			if (!result)
				entry->flags |= (*args[0].from == '^')
				     ? IMA_INMASK : IMA_MASK;
			break;
		case Opt_fsmagic:
			ima_log_string(ab, "fsmagic", args[0].from);

			if (entry->fsmagic) {
				result = -EINVAL;
				break;
			}

			result = kstrtoul(args[0].from, 16, &entry->fsmagic);
			if (!result)
				entry->flags |= IMA_FSMAGIC;
			break;
		case Opt_fsname:
			ima_log_string(ab, "fsname", args[0].from);

			entry->fsname = kstrdup(args[0].from, GFP_KERNEL);
			if (!entry->fsname) {
				result = -ENOMEM;
				break;
			}
			result = 0;
			entry->flags |= IMA_FSNAME;
			break;
		case Opt_fsuuid:
			ima_log_string(ab, "fsuuid", args[0].from);

			if (!uuid_is_null(&entry->fsuuid)) {
				result = -EINVAL;
				break;
			}

			result = uuid_parse(args[0].from, &entry->fsuuid);
			if (!result)
				entry->flags |= IMA_FSUUID;
			break;
		case Opt_uid_gt:
		case Opt_euid_gt:
			entry->uid_op = &uid_gt;
			/* fall through */
		case Opt_uid_lt:
		case Opt_euid_lt:
			if ((token == Opt_uid_lt) || (token == Opt_euid_lt))
				entry->uid_op = &uid_lt;
			/* fall through */
		case Opt_uid_eq:
		case Opt_euid_eq:
			uid_token = (token == Opt_uid_eq) ||
				    (token == Opt_uid_gt) ||
				    (token == Opt_uid_lt);

			ima_log_string_op(ab, uid_token ? "uid" : "euid",
					  args[0].from, entry->uid_op);

			if (uid_valid(entry->uid)) {
				result = -EINVAL;
				break;
			}

			result = kstrtoul(args[0].from, 10, &lnum);
			if (!result) {
				entry->uid = make_kuid(current_user_ns(),
						       (uid_t) lnum);
				if (!uid_valid(entry->uid) ||
				    (uid_t)lnum != lnum)
					result = -EINVAL;
				else
					entry->flags |= uid_token
					    ? IMA_UID : IMA_EUID;
			}
			break;
		case Opt_fowner_gt:
			entry->fowner_op = &uid_gt;
			/* fall through */
		case Opt_fowner_lt:
			if (token == Opt_fowner_lt)
				entry->fowner_op = &uid_lt;
			/* fall through */
		case Opt_fowner_eq:
			ima_log_string_op(ab, "fowner", args[0].from,
					  entry->fowner_op);

			if (uid_valid(entry->fowner)) {
				result = -EINVAL;
				break;
			}

			result = kstrtoul(args[0].from, 10, &lnum);
			if (!result) {
				entry->fowner = make_kuid(current_user_ns(), (uid_t)lnum);
				if (!uid_valid(entry->fowner) || (((uid_t)lnum) != lnum))
					result = -EINVAL;
				else
					entry->flags |= IMA_FOWNER;
			}
			break;
		case Opt_obj_user:
			ima_log_string(ab, "obj_user", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_OBJ_USER,
						   AUDIT_OBJ_USER);
			break;
		case Opt_obj_role:
			ima_log_string(ab, "obj_role", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_OBJ_ROLE,
						   AUDIT_OBJ_ROLE);
			break;
		case Opt_obj_type:
			ima_log_string(ab, "obj_type", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_OBJ_TYPE,
						   AUDIT_OBJ_TYPE);
			break;
		case Opt_subj_user:
			ima_log_string(ab, "subj_user", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_SUBJ_USER,
						   AUDIT_SUBJ_USER);
			break;
		case Opt_subj_role:
			ima_log_string(ab, "subj_role", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_SUBJ_ROLE,
						   AUDIT_SUBJ_ROLE);
			break;
		case Opt_subj_type:
			ima_log_string(ab, "subj_type", args[0].from);
			result = ima_lsm_rule_init(entry, args,
						   LSM_SUBJ_TYPE,
						   AUDIT_SUBJ_TYPE);
			break;
		case Opt_appraise_type:
			if (entry->action != APPRAISE) {
				result = -EINVAL;
				break;
			}

			ima_log_string(ab, "appraise_type", args[0].from);
			if ((strcmp(args[0].from, "imasig")) == 0)
				entry->flags |= IMA_DIGSIG_REQUIRED;
			else if (ima_hook_supports_modsig(entry->func) &&
				 strcmp(args[0].from, "imasig|modsig") == 0)
				entry->flags |= IMA_DIGSIG_REQUIRED |
						IMA_MODSIG_ALLOWED;
			else
				result = -EINVAL;
			break;
		case Opt_permit_directio:
			entry->flags |= IMA_PERMIT_DIRECTIO;
			break;
		case Opt_pcr:
			if (entry->action != MEASURE) {
				result = -EINVAL;
				break;
			}
			ima_log_string(ab, "pcr", args[0].from);

			result = kstrtoint(args[0].from, 10, &entry->pcr);
			if (result || INVALID_PCR(entry->pcr))
				result = -EINVAL;
			else
				entry->flags |= IMA_PCR;

			break;
		case Opt_template:
			ima_log_string(ab, "template", args[0].from);
			if (entry->action != MEASURE) {
				result = -EINVAL;
				break;
			}
			template_desc = lookup_template_desc(args[0].from);
			if (!template_desc || entry->template) {
				result = -EINVAL;
				break;
			}

			/*
			 * template_desc_init_fields() does nothing if
			 * the template is already initialised, so
			 * it's safe to do this unconditionally
			 */
			template_desc_init_fields(template_desc->fmt,
						 &(template_desc->fields),
						 &(template_desc->num_fields));
			entry->template = template_desc;
			break;
		case Opt_err:
			ima_log_string(ab, "UNKNOWN", p);
			result = -EINVAL;
			break;
		}
	}
	if (!result && (entry->action == UNKNOWN))
		result = -EINVAL;
	else if (entry->action == APPRAISE)
		temp_ima_appraise |= ima_appraise_flag(entry->func);

	if (!result && entry->flags & IMA_MODSIG_ALLOWED) {
		template_desc = entry->template ? entry->template :
						  ima_template_desc_current();
		check_template_modsig(template_desc);
	}

	audit_log_format(ab, "res=%d", !result);
	audit_log_end(ab);
	return result;
}