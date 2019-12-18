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
struct shader_var {int /*<<< orphan*/  mapping; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct shader_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFTOKEN_NAME ; 
 int PARSE_BREAK ; 
 int PARSE_CONTINUE ; 
 int PARSE_EOF ; 
 int PARSE_SUCCESS ; 
 int PARSE_UNEXPECTED_BREAK ; 
 int PARSE_UNEXPECTED_CONTINUE ; 
 int /*<<< orphan*/  cf_copy_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_go_to_valid_token (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_token_is (int /*<<< orphan*/ *,char*) ; 
 int cf_token_is_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static inline int sp_parse_struct_var(struct shader_parser *sp,
				      struct shader_var *var)
{
	int code;

	/* -------------------------------------- */
	/* variable type */

	if (!cf_next_valid_token(&sp->cfp))
		return PARSE_EOF;

	if (cf_token_is(&sp->cfp, ";"))
		return PARSE_CONTINUE;
	if (cf_token_is(&sp->cfp, "}"))
		return PARSE_BREAK;

	code = cf_token_is_type(&sp->cfp, CFTOKEN_NAME, "type name", ";");
	if (code != PARSE_SUCCESS)
		return code;

	cf_copy_token(&sp->cfp, &var->type);

	/* -------------------------------------- */
	/* variable name */

	if (!cf_next_valid_token(&sp->cfp))
		return PARSE_EOF;

	if (cf_token_is(&sp->cfp, ";"))
		return PARSE_UNEXPECTED_CONTINUE;
	if (cf_token_is(&sp->cfp, "}"))
		return PARSE_UNEXPECTED_BREAK;

	code = cf_token_is_type(&sp->cfp, CFTOKEN_NAME, "variable name", ";");
	if (code != PARSE_SUCCESS)
		return code;

	cf_copy_token(&sp->cfp, &var->name);

	/* -------------------------------------- */
	/* variable mapping if any (POSITION, TEXCOORD, etc) */

	if (!cf_next_valid_token(&sp->cfp))
		return PARSE_EOF;

	if (cf_token_is(&sp->cfp, ":")) {
		if (!cf_next_valid_token(&sp->cfp))
			return PARSE_EOF;

		if (cf_token_is(&sp->cfp, ";"))
			return PARSE_UNEXPECTED_CONTINUE;
		if (cf_token_is(&sp->cfp, "}"))
			return PARSE_UNEXPECTED_BREAK;

		code = cf_token_is_type(&sp->cfp, CFTOKEN_NAME, "mapping name",
					";");
		if (code != PARSE_SUCCESS)
			return code;

		cf_copy_token(&sp->cfp, &var->mapping);

		if (!cf_next_valid_token(&sp->cfp))
			return PARSE_EOF;
	}

	/* -------------------------------------- */

	if (!cf_token_is(&sp->cfp, ";")) {
		if (!cf_go_to_valid_token(&sp->cfp, ";", "}"))
			return PARSE_EOF;
		return PARSE_CONTINUE;
	}

	return PARSE_SUCCESS;
}