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
struct variable {TYPE_1__* type; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  ECPGt_const 136 
#define  ECPGt_int 135 
#define  ECPGt_long 134 
#define  ECPGt_long_long 133 
#define  ECPGt_short 132 
#define  ECPGt_unsigned_int 131 
#define  ECPGt_unsigned_long 130 
#define  ECPGt_unsigned_long_long 129 
#define  ECPGt_unsigned_short 128 
 int /*<<< orphan*/  ET_ERROR ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  base_yyout ; 
 struct variable* find_variable (char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
ECPGnumeric_lvalue(char *name)
{
	const struct variable *v = find_variable(name);

	switch (v->type->type)
	{
		case ECPGt_short:
		case ECPGt_int:
		case ECPGt_long:
		case ECPGt_long_long:
		case ECPGt_unsigned_short:
		case ECPGt_unsigned_int:
		case ECPGt_unsigned_long:
		case ECPGt_unsigned_long_long:
		case ECPGt_const:
			fputs(name, base_yyout);
			break;
		default:
			mmerror(PARSE_ERROR, ET_ERROR, "variable \"%s\" must have a numeric type", name);
			break;
	}
}