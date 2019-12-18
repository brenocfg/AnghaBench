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
struct shader_var {int /*<<< orphan*/  vars; int /*<<< orphan*/  name; } ;
struct shader_struct {int /*<<< orphan*/  vars; int /*<<< orphan*/  name; } ;
struct shader_parser {int /*<<< orphan*/  structs; int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
#define  PARSE_BREAK 132 
#define  PARSE_CONTINUE 131 
#define  PARSE_EOF 130 
 scalar_t__ PARSE_SUCCESS ; 
#define  PARSE_UNEXPECTED_BREAK 129 
#define  PARSE_UNEXPECTED_CONTINUE 128 
 int /*<<< orphan*/  cf_adderror_syntax_error (int /*<<< orphan*/ *) ; 
 scalar_t__ cf_next_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ cf_next_token_should_be (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct shader_var*) ; 
 int /*<<< orphan*/  shader_struct_free (struct shader_var*) ; 
 int /*<<< orphan*/  shader_struct_init (struct shader_var*) ; 
 int /*<<< orphan*/  shader_var_free (struct shader_var*) ; 
 int /*<<< orphan*/  shader_var_init (struct shader_var*) ; 
 int sp_parse_struct_var (struct shader_parser*,struct shader_var*) ; 

__attribute__((used)) static void sp_parse_struct(struct shader_parser *sp)
{
	struct shader_struct ss;
	shader_struct_init(&ss);

	if (cf_next_name(&sp->cfp, &ss.name, "name", ";") != PARSE_SUCCESS)
		goto error;
	if (cf_next_token_should_be(&sp->cfp, "{", ";", NULL) != PARSE_SUCCESS)
		goto error;

	/* get structure variables */
	while (true) {
		bool do_break = false;
		struct shader_var var;

		shader_var_init(&var);

		switch (sp_parse_struct_var(sp, &var)) {

		case PARSE_UNEXPECTED_CONTINUE:
			cf_adderror_syntax_error(&sp->cfp);
			/* Falls through. */
		case PARSE_CONTINUE:
			shader_var_free(&var);
			continue;

		case PARSE_UNEXPECTED_BREAK:
			cf_adderror_syntax_error(&sp->cfp);
			/* Falls through. */
		case PARSE_BREAK:
			shader_var_free(&var);
			do_break = true;
			break;

		case PARSE_EOF:
			shader_var_free(&var);
			goto error;
		}

		if (do_break)
			break;

		da_push_back(ss.vars, &var);
	}

	if (cf_next_token_should_be(&sp->cfp, ";", NULL, NULL) != PARSE_SUCCESS)
		goto error;

	da_push_back(sp->structs, &ss);
	return;

error:
	shader_struct_free(&ss);
}