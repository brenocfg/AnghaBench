#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct config_string {int /*<<< orphan*/ * variable; } ;
struct config_real {int /*<<< orphan*/ * variable; } ;
struct config_int {int /*<<< orphan*/ * variable; } ;
struct config_generic {int vartype; int /*<<< orphan*/  extra; } ;
struct config_enum {int /*<<< orphan*/ * variable; } ;
struct config_bool {int /*<<< orphan*/ * variable; } ;
struct TYPE_4__ {int /*<<< orphan*/  enumval; int /*<<< orphan*/  stringval; int /*<<< orphan*/  realval; int /*<<< orphan*/  intval; int /*<<< orphan*/  boolval; } ;
struct TYPE_5__ {int /*<<< orphan*/  extra; TYPE_1__ val; } ;
typedef  TYPE_2__ config_var_value ;

/* Variables and functions */
#define  PGC_BOOL 132 
#define  PGC_ENUM 131 
#define  PGC_INT 130 
#define  PGC_REAL 129 
#define  PGC_STRING 128 
 int /*<<< orphan*/  set_extra_field (struct config_generic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_string_field (struct config_string*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_stack_value(struct config_generic *gconf, config_var_value *val)
{
	switch (gconf->vartype)
	{
		case PGC_BOOL:
			val->val.boolval =
				*((struct config_bool *) gconf)->variable;
			break;
		case PGC_INT:
			val->val.intval =
				*((struct config_int *) gconf)->variable;
			break;
		case PGC_REAL:
			val->val.realval =
				*((struct config_real *) gconf)->variable;
			break;
		case PGC_STRING:
			set_string_field((struct config_string *) gconf,
							 &(val->val.stringval),
							 *((struct config_string *) gconf)->variable);
			break;
		case PGC_ENUM:
			val->val.enumval =
				*((struct config_enum *) gconf)->variable;
			break;
	}
	set_extra_field(gconf, &(val->extra), gconf->extra);
}