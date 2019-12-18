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
struct TYPE_2__ {struct ECPGtype* element; struct ECPGstruct_member* members; } ;
struct ECPGtype {int type; TYPE_1__ u; } ;
struct ECPGstruct_member {struct ECPGtype* type; struct ECPGstruct_member* next; } ;

/* Variables and functions */
#define  ECPGt_array 138 
#define  ECPGt_int 137 
#define  ECPGt_long 136 
#define  ECPGt_long_long 135 
#define  ECPGt_short 134 
#define  ECPGt_struct 133 
#define  ECPGt_union 132 
#define  ECPGt_unsigned_int 131 
#define  ECPGt_unsigned_long 130 
#define  ECPGt_unsigned_long_long 129 
#define  ECPGt_unsigned_short 128 
 int /*<<< orphan*/  ET_ERROR ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
check_indicator(struct ECPGtype *var)
{
	/* make sure this is a valid indicator variable */
	switch (var->type)
	{
			struct ECPGstruct_member *p;

		case ECPGt_short:
		case ECPGt_int:
		case ECPGt_long:
		case ECPGt_long_long:
		case ECPGt_unsigned_short:
		case ECPGt_unsigned_int:
		case ECPGt_unsigned_long:
		case ECPGt_unsigned_long_long:
			break;

		case ECPGt_struct:
		case ECPGt_union:
			for (p = var->u.members; p; p = p->next)
				check_indicator(p->type);
			break;

		case ECPGt_array:
			check_indicator(var->u.element);
			break;
		default:
			mmerror(PARSE_ERROR, ET_ERROR, "indicator variable must have an integer type");
			break;
	}
}