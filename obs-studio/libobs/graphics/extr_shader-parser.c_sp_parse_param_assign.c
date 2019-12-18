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
struct shader_var {int dummy; } ;
struct shader_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 scalar_t__ PARSE_SUCCESS ; 
 int /*<<< orphan*/  cf_next_valid_token (int /*<<< orphan*/ *) ; 
 scalar_t__ sp_parse_param_assignment_val (struct shader_parser*,struct shader_var*) ; 

__attribute__((used)) static inline bool sp_parse_param_assign(struct shader_parser *sp,
					 struct shader_var *param)
{
	if (sp_parse_param_assignment_val(sp, param) != PARSE_SUCCESS)
		return false;

	if (!cf_next_valid_token(&sp->cfp))
		return false;

	return true;
}