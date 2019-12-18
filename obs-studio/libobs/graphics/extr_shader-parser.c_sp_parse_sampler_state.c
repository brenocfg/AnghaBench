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
struct shader_sampler {int /*<<< orphan*/  name; } ;
struct shader_parser {int /*<<< orphan*/  samplers; int /*<<< orphan*/  cfp; } ;
struct cf_token {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int PARSE_EOF ; 
 scalar_t__ PARSE_SUCCESS ; 
 scalar_t__ cf_next_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ cf_next_token_should_be (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cf_peek_valid_token (int /*<<< orphan*/ *,struct cf_token*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct shader_sampler*) ; 
 int /*<<< orphan*/  shader_sampler_free (struct shader_sampler*) ; 
 int /*<<< orphan*/  shader_sampler_init (struct shader_sampler*) ; 
 int sp_parse_sampler_state_item (struct shader_parser*,struct shader_sampler*) ; 
 scalar_t__ strref_cmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void sp_parse_sampler_state(struct shader_parser *sp)
{
	struct shader_sampler ss;
	struct cf_token peek;
	shader_sampler_init(&ss);

	if (cf_next_name(&sp->cfp, &ss.name, "name", ";") != PARSE_SUCCESS)
		goto error;
	if (cf_next_token_should_be(&sp->cfp, "{", ";", NULL) != PARSE_SUCCESS)
		goto error;

	if (!cf_peek_valid_token(&sp->cfp, &peek))
		goto error;

	while (strref_cmp(&peek.str, "}") != 0) {
		int ret = sp_parse_sampler_state_item(sp, &ss);
		if (ret == PARSE_EOF)
			goto error;

		if (!cf_peek_valid_token(&sp->cfp, &peek))
			goto error;
	}

	if (cf_next_token_should_be(&sp->cfp, "}", ";", NULL) != PARSE_SUCCESS)
		goto error;
	if (cf_next_token_should_be(&sp->cfp, ";", NULL, NULL) != PARSE_SUCCESS)
		goto error;

	da_push_back(sp->samplers, &ss);
	return;

error:
	shader_sampler_free(&ss);
}