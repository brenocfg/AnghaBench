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
struct shader_sampler {int /*<<< orphan*/  values; int /*<<< orphan*/  states; } ;
struct shader_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int PARSE_SUCCESS ; 
 int /*<<< orphan*/  bfree (char*) ; 
 int cf_next_name (int /*<<< orphan*/ *,char**,char*,char*) ; 
 int cf_next_token_copy (int /*<<< orphan*/ *,char**) ; 
 int cf_next_token_should_be (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int sp_parse_sampler_state_item(struct shader_parser *sp,
				       struct shader_sampler *ss)
{
	int ret;
	char *state = NULL, *value = NULL;

	ret = cf_next_name(&sp->cfp, &state, "state name", ";");
	if (ret != PARSE_SUCCESS)
		goto fail;

	ret = cf_next_token_should_be(&sp->cfp, "=", ";", NULL);
	if (ret != PARSE_SUCCESS)
		goto fail;

	ret = cf_next_token_copy(&sp->cfp, &value);
	if (ret != PARSE_SUCCESS)
		goto fail;

	ret = cf_next_token_should_be(&sp->cfp, ";", ";", NULL);
	if (ret != PARSE_SUCCESS)
		goto fail;

	da_push_back(ss->states, &state);
	da_push_back(ss->values, &value);
	return ret;

fail:
	bfree(state);
	bfree(value);
	return ret;
}