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
struct shader_var {int /*<<< orphan*/  type; } ;
struct gl_shader_parser {int /*<<< orphan*/  gl_string; } ;
struct cf_token {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ astrcmp_n (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dstr_cat (int /*<<< orphan*/ *,char*) ; 
 int gl_write_mul (struct gl_shader_parser*,struct cf_token**) ; 
 int gl_write_saturate (struct gl_shader_parser*,struct cf_token**) ; 
 int gl_write_texture_code (struct gl_shader_parser*,struct cf_token**,struct shader_var*) ; 
 struct shader_var* sp_getparam (struct gl_shader_parser*,struct cf_token*) ; 
 scalar_t__ strref_cmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bool gl_write_intrinsic(struct gl_shader_parser *glsp,
			       struct cf_token **p_token)
{
	struct cf_token *token = *p_token;
	bool written = true;

	if (strref_cmp(&token->str, "atan2") == 0) {
		dstr_cat(&glsp->gl_string, "atan2");
	} else if (strref_cmp(&token->str, "ddx") == 0) {
		dstr_cat(&glsp->gl_string, "dFdx");
	} else if (strref_cmp(&token->str, "ddy") == 0) {
		dstr_cat(&glsp->gl_string, "dFdy");
	} else if (strref_cmp(&token->str, "frac") == 0) {
		dstr_cat(&glsp->gl_string, "fract");
	} else if (strref_cmp(&token->str, "lerp") == 0) {
		dstr_cat(&glsp->gl_string, "mix");
	} else if (strref_cmp(&token->str, "fmod") == 0) {
		dstr_cat(&glsp->gl_string, "mod");
	} else if (strref_cmp(&token->str, "rsqrt") == 0) {
		dstr_cat(&glsp->gl_string, "inversesqrt");
	} else if (strref_cmp(&token->str, "saturate") == 0) {
		written = gl_write_saturate(glsp, &token);
	} else if (strref_cmp(&token->str, "mul") == 0) {
		written = gl_write_mul(glsp, &token);
	} else {
		struct shader_var *var = sp_getparam(glsp, token);
		if (var && astrcmp_n(var->type, "texture", 7) == 0)
			written = gl_write_texture_code(glsp, &token, var);
		else
			written = false;
	}

	if (written)
		*p_token = token;
	return written;
}