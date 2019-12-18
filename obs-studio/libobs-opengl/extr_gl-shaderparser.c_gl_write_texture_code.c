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
struct shader_var {int dummy; } ;
struct cf_parser {struct cf_token* cur_token; } ;
struct TYPE_2__ {struct cf_parser cfp; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; TYPE_1__ parser; } ;
struct cf_token {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_next_token (struct cf_parser*) ; 
 scalar_t__ cf_token_is (struct cf_parser*,char*) ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gl_write_function_contents (struct gl_shader_parser*,struct cf_token**,char*) ; 
 int gl_write_texture_call (struct gl_shader_parser*,struct shader_var*,char*,int) ; 

__attribute__((used)) static bool gl_write_texture_code(struct gl_shader_parser *glsp,
				  struct cf_token **p_token,
				  struct shader_var *var)
{
	struct cf_parser *cfp = &glsp->parser.cfp;
	bool written = false;
	cfp->cur_token = *p_token;

	if (!cf_next_token(cfp))
		return false;
	if (!cf_token_is(cfp, "."))
		return false;
	if (!cf_next_token(cfp))
		return false;

	const char *function_end = ")";

	if (cf_token_is(cfp, "Sample"))
		written = gl_write_texture_call(glsp, var, "texture", true);
	else if (cf_token_is(cfp, "SampleBias"))
		written = gl_write_texture_call(glsp, var, "texture", true);
	else if (cf_token_is(cfp, "SampleGrad"))
		written = gl_write_texture_call(glsp, var, "textureGrad", true);
	else if (cf_token_is(cfp, "SampleLevel"))
		written = gl_write_texture_call(glsp, var, "textureLod", true);
	else if (cf_token_is(cfp, "Load")) {
		written = gl_write_texture_call(glsp, var, "texelFetch", false);
		dstr_cat(&glsp->gl_string, "(");
		function_end = ").xy, 0)";
	}

	if (!written)
		return false;

	if (!cf_next_token(cfp))
		return false;

	gl_write_function_contents(glsp, &cfp->cur_token, ")");
	dstr_cat(&glsp->gl_string, function_end);

	*p_token = cfp->cur_token;
	return true;
}