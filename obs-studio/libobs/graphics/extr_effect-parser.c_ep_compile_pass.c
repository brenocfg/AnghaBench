#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct gs_effect_pass* array; } ;
struct gs_effect_technique {TYPE_1__ passes; } ;
struct gs_effect_pass {char* name; int /*<<< orphan*/  section; } ;
struct TYPE_4__ {struct ep_pass* array; } ;
struct ep_technique {TYPE_2__ passes; } ;
struct ep_pass {int /*<<< orphan*/  name; } ;
struct effect_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFFECT_PASS ; 
 int /*<<< orphan*/  GS_SHADER_PIXEL ; 
 int /*<<< orphan*/  GS_SHADER_VERTEX ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,size_t,char*) ; 
 char* bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep_compile_pass_shader (struct effect_parser*,struct gs_effect_technique*,struct gs_effect_pass*,struct ep_pass*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ep_compile_pass(struct effect_parser *ep,
			    struct gs_effect_technique *tech,
			    struct ep_technique *tech_in, size_t idx)
{
	struct gs_effect_pass *pass;
	struct ep_pass *pass_in;
	bool success = true;

	pass = tech->passes.array + idx;
	pass_in = tech_in->passes.array + idx;

	pass->name = bstrdup(pass_in->name);
	pass->section = EFFECT_PASS;

#if defined(_DEBUG) && defined(_DEBUG_SHADERS)
	blog(LOG_DEBUG, "\t\t[%4lld] Pass '%s':", idx, pass->name);
#endif

	if (!ep_compile_pass_shader(ep, tech, pass, pass_in, idx,
				    GS_SHADER_VERTEX)) {
		success = false;
		blog(LOG_ERROR, "Pass (%zu) <%s> missing vertex shader!", idx,
		     pass->name ? pass->name : "");
	}
	if (!ep_compile_pass_shader(ep, tech, pass, pass_in, idx,
				    GS_SHADER_PIXEL)) {
		success = false;
		blog(LOG_ERROR, "Pass (%zu) <%s> missing pixel shader!", idx,
		     pass->name ? pass->name : "");
	}
	return success;
}