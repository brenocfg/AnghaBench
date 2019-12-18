#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cf_parser {struct cf_token* cur_token; } ;
struct TYPE_2__ {struct cf_parser cfp; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; TYPE_1__ parser; } ;
struct cf_token {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_next_token (struct cf_parser*) ; 
 int /*<<< orphan*/  cf_token_is (struct cf_parser*,char*) ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gl_write_function_contents (struct gl_shader_parser*,struct cf_token**,char*) ; 

__attribute__((used)) static bool gl_write_saturate(struct gl_shader_parser *glsp,
			      struct cf_token **p_token)
{
	struct cf_parser *cfp = &glsp->parser.cfp;
	cfp->cur_token = *p_token;

	if (!cf_next_token(cfp))
		return false;
	if (!cf_token_is(cfp, "("))
		return false;

	dstr_cat(&glsp->gl_string, "clamp");
	gl_write_function_contents(glsp, &cfp->cur_token, ")");
	dstr_cat(&glsp->gl_string, ", 0.0, 1.0)");

	*p_token = cfp->cur_token;
	return true;
}