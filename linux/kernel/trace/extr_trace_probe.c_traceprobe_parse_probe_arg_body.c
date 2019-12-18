#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct probe_arg {scalar_t__ count; int offset; int dynamic; void* code; TYPE_1__* type; int /*<<< orphan*/  fmt; int /*<<< orphan*/  comm; } ;
struct fetch_insn {scalar_t__ op; int size; int param; struct fetch_insn* data; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int size; char* fmttype; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_TOO_LONG ; 
 int /*<<< orphan*/  ARRAY_NO_CLOSE ; 
 int /*<<< orphan*/  ARRAY_TOO_BIG ; 
 int /*<<< orphan*/  BAD_ARRAY_NUM ; 
 int /*<<< orphan*/  BAD_ARRAY_SUFFIX ; 
 int /*<<< orphan*/  BAD_BITFIELD ; 
 int /*<<< orphan*/  BAD_STRING ; 
 int /*<<< orphan*/  BAD_TYPE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FETCH_INSN_MAX ; 
 scalar_t__ FETCH_NOP_SYMBOL ; 
 scalar_t__ FETCH_OP_COMM ; 
 scalar_t__ FETCH_OP_DATA ; 
 scalar_t__ FETCH_OP_DEREF ; 
 void* FETCH_OP_END ; 
 scalar_t__ FETCH_OP_IMM ; 
 scalar_t__ FETCH_OP_LP_ARRAY ; 
 scalar_t__ FETCH_OP_NOP ; 
 scalar_t__ FETCH_OP_ST_MEM ; 
 scalar_t__ FETCH_OP_ST_RAW ; 
 scalar_t__ FETCH_OP_ST_STRING ; 
 scalar_t__ FETCH_OP_ST_UMEM ; 
 scalar_t__ FETCH_OP_ST_USTRING ; 
 scalar_t__ FETCH_OP_UDEREF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ARGSTR_LEN ; 
 scalar_t__ MAX_ARRAY_LEN ; 
 int /*<<< orphan*/  NO_ARG_BODY ; 
 int /*<<< orphan*/  TOO_MANY_OPS ; 
 int __parse_bitfield_probe_arg (char*,TYPE_1__*,struct fetch_insn**) ; 
 void* find_fetch_type (char*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fetch_insn*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtouint (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (void*,struct fetch_insn*,int) ; 
 int parse_probe_arg (char*,TYPE_1__*,struct fetch_insn**,struct fetch_insn*,unsigned int,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  trace_probe_log_err (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int traceprobe_parse_probe_arg_body(char *arg, ssize_t *size,
		struct probe_arg *parg, unsigned int flags, int offset)
{
	struct fetch_insn *code, *scode, *tmp = NULL;
	char *t, *t2, *t3;
	int ret, len;

	len = strlen(arg);
	if (len > MAX_ARGSTR_LEN) {
		trace_probe_log_err(offset, ARG_TOO_LONG);
		return -EINVAL;
	} else if (len == 0) {
		trace_probe_log_err(offset, NO_ARG_BODY);
		return -EINVAL;
	}

	parg->comm = kstrdup(arg, GFP_KERNEL);
	if (!parg->comm)
		return -ENOMEM;

	t = strchr(arg, ':');
	if (t) {
		*t = '\0';
		t2 = strchr(++t, '[');
		if (t2) {
			*t2++ = '\0';
			t3 = strchr(t2, ']');
			if (!t3) {
				offset += t2 + strlen(t2) - arg;
				trace_probe_log_err(offset,
						    ARRAY_NO_CLOSE);
				return -EINVAL;
			} else if (t3[1] != '\0') {
				trace_probe_log_err(offset + t3 + 1 - arg,
						    BAD_ARRAY_SUFFIX);
				return -EINVAL;
			}
			*t3 = '\0';
			if (kstrtouint(t2, 0, &parg->count) || !parg->count) {
				trace_probe_log_err(offset + t2 - arg,
						    BAD_ARRAY_NUM);
				return -EINVAL;
			}
			if (parg->count > MAX_ARRAY_LEN) {
				trace_probe_log_err(offset + t2 - arg,
						    ARRAY_TOO_BIG);
				return -EINVAL;
			}
		}
	}

	/*
	 * Since $comm and immediate string can not be dereferred,
	 * we can find those by strcmp.
	 */
	if (strcmp(arg, "$comm") == 0 || strncmp(arg, "\\\"", 2) == 0) {
		/* The type of $comm must be "string", and not an array. */
		if (parg->count || (t && strcmp(t, "string")))
			return -EINVAL;
		parg->type = find_fetch_type("string");
	} else
		parg->type = find_fetch_type(t);
	if (!parg->type) {
		trace_probe_log_err(offset + (t ? (t - arg) : 0), BAD_TYPE);
		return -EINVAL;
	}
	parg->offset = *size;
	*size += parg->type->size * (parg->count ?: 1);

	if (parg->count) {
		len = strlen(parg->type->fmttype) + 6;
		parg->fmt = kmalloc(len, GFP_KERNEL);
		if (!parg->fmt)
			return -ENOMEM;
		snprintf(parg->fmt, len, "%s[%d]", parg->type->fmttype,
			 parg->count);
	}

	code = tmp = kcalloc(FETCH_INSN_MAX, sizeof(*code), GFP_KERNEL);
	if (!code)
		return -ENOMEM;
	code[FETCH_INSN_MAX - 1].op = FETCH_OP_END;

	ret = parse_probe_arg(arg, parg->type, &code, &code[FETCH_INSN_MAX - 1],
			      flags, offset);
	if (ret)
		goto fail;

	/* Store operation */
	if (!strcmp(parg->type->name, "string") ||
	    !strcmp(parg->type->name, "ustring")) {
		if (code->op != FETCH_OP_DEREF && code->op != FETCH_OP_UDEREF &&
		    code->op != FETCH_OP_IMM && code->op != FETCH_OP_COMM &&
		    code->op != FETCH_OP_DATA) {
			trace_probe_log_err(offset + (t ? (t - arg) : 0),
					    BAD_STRING);
			ret = -EINVAL;
			goto fail;
		}
		if ((code->op == FETCH_OP_IMM || code->op == FETCH_OP_COMM) ||
		     parg->count) {
			/*
			 * IMM, DATA and COMM is pointing actual address, those
			 * must be kept, and if parg->count != 0, this is an
			 * array of string pointers instead of string address
			 * itself.
			 */
			code++;
			if (code->op != FETCH_OP_NOP) {
				trace_probe_log_err(offset, TOO_MANY_OPS);
				ret = -EINVAL;
				goto fail;
			}
		}
		/* If op == DEREF, replace it with STRING */
		if (!strcmp(parg->type->name, "ustring") ||
		    code->op == FETCH_OP_UDEREF)
			code->op = FETCH_OP_ST_USTRING;
		else
			code->op = FETCH_OP_ST_STRING;
		code->size = parg->type->size;
		parg->dynamic = true;
	} else if (code->op == FETCH_OP_DEREF) {
		code->op = FETCH_OP_ST_MEM;
		code->size = parg->type->size;
	} else if (code->op == FETCH_OP_UDEREF) {
		code->op = FETCH_OP_ST_UMEM;
		code->size = parg->type->size;
	} else {
		code++;
		if (code->op != FETCH_OP_NOP) {
			trace_probe_log_err(offset, TOO_MANY_OPS);
			ret = -EINVAL;
			goto fail;
		}
		code->op = FETCH_OP_ST_RAW;
		code->size = parg->type->size;
	}
	scode = code;
	/* Modify operation */
	if (t != NULL) {
		ret = __parse_bitfield_probe_arg(t, parg->type, &code);
		if (ret) {
			trace_probe_log_err(offset + t - arg, BAD_BITFIELD);
			goto fail;
		}
	}
	/* Loop(Array) operation */
	if (parg->count) {
		if (scode->op != FETCH_OP_ST_MEM &&
		    scode->op != FETCH_OP_ST_STRING &&
		    scode->op != FETCH_OP_ST_USTRING) {
			trace_probe_log_err(offset + (t ? (t - arg) : 0),
					    BAD_STRING);
			ret = -EINVAL;
			goto fail;
		}
		code++;
		if (code->op != FETCH_OP_NOP) {
			trace_probe_log_err(offset, TOO_MANY_OPS);
			ret = -EINVAL;
			goto fail;
		}
		code->op = FETCH_OP_LP_ARRAY;
		code->param = parg->count;
	}
	code++;
	code->op = FETCH_OP_END;

	/* Shrink down the code buffer */
	parg->code = kcalloc(code - tmp + 1, sizeof(*code), GFP_KERNEL);
	if (!parg->code)
		ret = -ENOMEM;
	else
		memcpy(parg->code, tmp, sizeof(*code) * (code - tmp + 1));

fail:
	if (ret) {
		for (code = tmp; code < tmp + FETCH_INSN_MAX; code++)
			if (code->op == FETCH_NOP_SYMBOL ||
			    code->op == FETCH_OP_DATA)
				kfree(code->data);
	}
	kfree(tmp);

	return ret;
}