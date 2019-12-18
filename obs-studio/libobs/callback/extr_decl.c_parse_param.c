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
struct strref {int dummy; } ;
struct decl_param {scalar_t__ flags; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct decl_info {int /*<<< orphan*/  params; } ;
struct cf_parser {int dummy; } ;

/* Variables and functions */
 scalar_t__ CALL_PARAM_IN ; 
 int PARSE_CONTINUE ; 
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  TYPE_OR_STORAGE ; 
 int /*<<< orphan*/  cf_adderror_expecting (struct cf_parser*,char*) ; 
 int /*<<< orphan*/  cf_go_to_token (struct cf_parser*,char*,char*) ; 
 int cf_next_name (struct cf_parser*,int /*<<< orphan*/ *,char*,char*) ; 
 int cf_next_name_ref (struct cf_parser*,struct strref*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct decl_param*) ; 
 int /*<<< orphan*/  err_existing_name (struct cf_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_reserved_name (struct cf_parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_type (struct strref*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ is_in_out_specifier (struct cf_parser*,struct strref*,scalar_t__*) ; 
 scalar_t__ is_reserved_name (int /*<<< orphan*/ ) ; 
 scalar_t__ name_exists (struct decl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_param(struct cf_parser *cfp, struct decl_info *decl)
{
	struct strref ref;
	int code;
	struct decl_param param = {0};

	/* get storage specifiers */
	code = cf_next_name_ref(cfp, &ref, TYPE_OR_STORAGE, ",");
	if (code != PARSE_SUCCESS)
		return code;

	while (is_in_out_specifier(cfp, &ref, &param.flags)) {
		code = cf_next_name_ref(cfp, &ref, TYPE_OR_STORAGE, ",");
		if (code != PARSE_SUCCESS)
			return code;
	}

	/* parameters not marked with specifiers are input parameters */
	if (param.flags == 0)
		param.flags = CALL_PARAM_IN;

	if (!get_type(&ref, &param.type, false)) {
		cf_adderror_expecting(cfp, "type");
		cf_go_to_token(cfp, ",", ")");
		return PARSE_CONTINUE;
	}

	/* name */
	code = cf_next_name(cfp, &param.name, "parameter name", ",");
	if (code != PARSE_SUCCESS)
		return code;

	if (name_exists(decl, param.name))
		err_existing_name(cfp, param.name);

	if (is_reserved_name(param.name))
		err_reserved_name(cfp, param.name);

	da_push_back(decl->params, &param);
	return PARSE_SUCCESS;
}