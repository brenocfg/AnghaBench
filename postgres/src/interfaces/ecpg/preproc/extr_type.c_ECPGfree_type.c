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
struct TYPE_2__ {int /*<<< orphan*/  members; struct ECPGtype* element; } ;
struct ECPGtype {int type; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGfree_struct_member (int /*<<< orphan*/ ) ; 
#define  ECPGt_array 130 
#define  ECPGt_struct 129 
#define  ECPGt_union 128 
 int /*<<< orphan*/  ET_ERROR ; 
 int /*<<< orphan*/  IS_SIMPLE_TYPE (int) ; 
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  base_yyerror (char*) ; 
 int /*<<< orphan*/  free (struct ECPGtype*) ; 
 int /*<<< orphan*/  mmerror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
ECPGfree_type(struct ECPGtype *type)
{
	if (!IS_SIMPLE_TYPE(type->type))
	{
		switch (type->type)
		{
			case ECPGt_array:
				switch (type->u.element->type)
				{
					case ECPGt_array:
						base_yyerror("internal error: found multidimensional array\n");
						break;
					case ECPGt_struct:
					case ECPGt_union:
						/* Array of structs. */
						ECPGfree_struct_member(type->u.element->u.members);
						free(type->u.element);
						break;
					default:
						if (!IS_SIMPLE_TYPE(type->u.element->type))
							base_yyerror("internal error: unknown datatype, please report this to <pgsql-bugs@lists.postgresql.org>");

						free(type->u.element);
				}
				break;
			case ECPGt_struct:
			case ECPGt_union:
				ECPGfree_struct_member(type->u.members);
				break;
			default:
				mmerror(PARSE_ERROR, ET_ERROR, "unrecognized variable type code %d", type->type);
				break;
		}
	}
	free(type);
}