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
struct ep_var {scalar_t__ var_type; char* type; char* name; char* mapping; } ;
struct dstr {int dummy; } ;

/* Variables and functions */
 scalar_t__ EP_VAR_INOUT ; 
 scalar_t__ EP_VAR_OUT ; 
 scalar_t__ EP_VAR_UNIFORM ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 

__attribute__((used)) static inline void ep_write_var(struct dstr *shader, struct ep_var *var)
{
	if (var->var_type == EP_VAR_INOUT)
		dstr_cat(shader, "inout ");
	else if (var->var_type == EP_VAR_OUT)
		dstr_cat(shader, "out ");
	else if (var->var_type == EP_VAR_UNIFORM)
		dstr_cat(shader, "uniform ");
	// The "in" input modifier is implied by default, so leave it blank
	// in that case.

	dstr_cat(shader, var->type);
	dstr_cat(shader, " ");
	dstr_cat(shader, var->name);

	if (var->mapping) {
		dstr_cat(shader, " : ");
		dstr_cat(shader, var->mapping);
	}
}