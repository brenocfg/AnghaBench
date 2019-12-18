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
struct shader_var {size_t gl_sampler_id; char* name; } ;
struct cf_parser {int /*<<< orphan*/  cur_token; } ;
struct TYPE_2__ {struct cf_parser cfp; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; TYPE_1__ parser; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_next_token (struct cf_parser*) ; 
 int /*<<< orphan*/  cf_token_is (struct cf_parser*,char*) ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char const*) ; 
 size_t sp_getsampler (struct gl_shader_parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool gl_write_texture_call(struct gl_shader_parser *glsp,
					 struct shader_var *var,
					 const char *call, bool sampler)
{
	struct cf_parser *cfp = &glsp->parser.cfp;

	if (!cf_next_token(cfp))
		return false;
	if (!cf_token_is(cfp, "("))
		return false;

	if (sampler) {
		if (!cf_next_token(cfp))
			return false;
		const size_t sampler_id = sp_getsampler(glsp, cfp->cur_token);
		if (sampler_id == (size_t)-1)
			return false;
		if (!cf_next_token(cfp))
			return false;
		if (!cf_token_is(cfp, ","))
			return false;

		var->gl_sampler_id = sampler_id;
	}

	dstr_cat(&glsp->gl_string, call);
	dstr_cat(&glsp->gl_string, "(");
	dstr_cat(&glsp->gl_string, var->name);
	dstr_cat(&glsp->gl_string, ", ");
	return true;
}