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
struct shader_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEX_ERROR ; 
 int PARSE_CONTINUE ; 
 scalar_t__ astrcmp_n (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cf_adderror (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sp_parse_param_assign_float_array (struct shader_parser*,struct shader_var*) ; 
 int sp_parse_param_assign_intfloat (struct shader_parser*,struct shader_var*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sp_parse_param_assignment_val(struct shader_parser *sp,
					 struct shader_var *param)
{
	if (strcmp(param->type, "int") == 0)
		return sp_parse_param_assign_intfloat(sp, param, false);
	else if (strcmp(param->type, "float") == 0)
		return sp_parse_param_assign_intfloat(sp, param, true);
	else if (astrcmp_n(param->type, "float", 5) == 0)
		return sp_parse_param_assign_float_array(sp, param);

	cf_adderror(&sp->cfp, "Invalid type '$1' used for assignment",
		    LEX_ERROR, param->type, NULL, NULL);

	return PARSE_CONTINUE;
}