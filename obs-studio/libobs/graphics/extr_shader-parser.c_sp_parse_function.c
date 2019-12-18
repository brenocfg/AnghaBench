#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cur_token; } ;
struct shader_parser {int /*<<< orphan*/  funcs; TYPE_1__ cfp; } ;
struct shader_func {char* mapping; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  cf_adderror_expecting (TYPE_1__*,char*) ; 
 int cf_next_name (TYPE_1__*,char**,char*,char*) ; 
 int /*<<< orphan*/  cf_next_token (TYPE_1__*) ; 
 int /*<<< orphan*/  cf_next_valid_token (TYPE_1__*) ; 
 int /*<<< orphan*/  cf_pass_pair (TYPE_1__*,char,char) ; 
 scalar_t__ cf_token_is (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct shader_func*) ; 
 int /*<<< orphan*/  shader_func_free (struct shader_func*) ; 
 int /*<<< orphan*/  shader_func_init (struct shader_func*,char*,char*) ; 
 int /*<<< orphan*/  sp_parse_func_params (struct shader_parser*,struct shader_func*) ; 

__attribute__((used)) static void sp_parse_function(struct shader_parser *sp, char *type, char *name)
{
	struct shader_func func;

	shader_func_init(&func, type, name);
	if (!sp_parse_func_params(sp, &func))
		goto error;

	if (!cf_next_valid_token(&sp->cfp))
		goto error;

	/* if function is mapped to something, for example COLOR */
	if (cf_token_is(&sp->cfp, ":")) {
		char *mapping = NULL;
		int errorcode =
			cf_next_name(&sp->cfp, &mapping, "mapping", "{");
		if (errorcode != PARSE_SUCCESS)
			goto error;

		func.mapping = mapping;

		if (!cf_next_valid_token(&sp->cfp))
			goto error;
	}

	if (!cf_token_is(&sp->cfp, "{")) {
		cf_adderror_expecting(&sp->cfp, "{");
		goto error;
	}

	func.start = sp->cfp.cur_token;
	if (!cf_pass_pair(&sp->cfp, '{', '}'))
		goto error;

	/* it is established that the current token is '}' if we reach this */
	cf_next_token(&sp->cfp);

	func.end = sp->cfp.cur_token;
	da_push_back(sp->funcs, &func);
	return;

error:
	shader_func_free(&func);
}