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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {char* type; int /*<<< orphan*/  name; int /*<<< orphan*/  isarg; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; int /*<<< orphan*/  delta; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_1__ RAnalVar ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  r_anal_var_retype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_str_endswith (char*,char*) ; 
 scalar_t__ r_str_startswith (char*,char*) ; 
 int /*<<< orphan*/  r_str_trim (char*) ; 
 int /*<<< orphan*/  r_strbuf_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_free (int /*<<< orphan*/ *) ; 
 char* r_strbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (char*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void var_retype(RAnal *anal, RAnalVar *var, const char *vname, char *type, ut64 addr, bool ref, bool pfx) {
	if (!type || !var) {
		return;
	}
	char *trim = type;
	r_str_trim (trim);
	if (!*trim) {
		return;
	}
	bool is_ptr = (vname && *vname == '*')? true: false;
	if (!strncmp (trim, "int", 3) || (!is_ptr && !strcmp (trim, "void"))) {
		// default or void type
		return;
	}
	const char *expand = var->type;
	if (!strcmp(var->type, "int32_t")) {
		expand = "int";
	} else if (!strcmp(var->type, "uint32_t")) {
		expand = "unsigned int";
	} else if (!strcmp(var->type, "uint64_t")) {
		expand = "unsigned long long";
	}
	const char *tmp = strstr (expand, "int");
	bool is_default = tmp? true: false;
	if (!is_default && strncmp (var->type, "void", 4)) {
		// return since type is already propagated
		// except for "void *", since "void *" => "char *" is possible
		return;
	}
	RStrBuf *sb = r_strbuf_new ("");
	if (pfx) {
		if (is_default && strncmp (var->type, "signed", 6)) {
			r_strbuf_setf (sb, "%s %s", type, tmp);
		} else {
			r_strbuf_free (sb);
			return;
		}
	} else {
		r_strbuf_set (sb, trim);
	}
	if (!strncmp (r_strbuf_get (sb), "const ", 6)) {
		// Dropping const from type
		//TODO: Inferring const type
		r_strbuf_setf (sb, "%s", type + 6);
	}
	if (is_ptr) {
		//type *ptr => type *
		r_strbuf_append (sb, " *");
	}
	if (ref) {
		if (r_str_endswith (r_strbuf_get (sb), "*")) { // type * => type **
			r_strbuf_append (sb, "*");
		} else {   //  type => type *
			r_strbuf_append (sb, " *");
		}
	}

	char* tmp1 = r_strbuf_get (sb);
	if (r_str_startswith (tmp1, "unsigned long long")) {
		r_strbuf_set (sb, "uint64_t");
	} else if (r_str_startswith (tmp1, "unsigned")) {
		r_strbuf_set (sb, "uint32_t");
	} else if (r_str_startswith (tmp1, "int")) {
		r_strbuf_set (sb, "int32_t");
	}
	r_anal_var_retype (anal, addr, 1, var->delta, var->kind, r_strbuf_get (sb), var->size, var->isarg, var->name);
	r_strbuf_free (sb);
}