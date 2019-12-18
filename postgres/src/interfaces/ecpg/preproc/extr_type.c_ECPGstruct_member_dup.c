#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ECPGtype {int dummy; } ;
struct ECPGstruct_member {struct ECPGstruct_member* next; int /*<<< orphan*/  name; TYPE_4__* type; } ;
struct TYPE_7__ {TYPE_2__* element; int /*<<< orphan*/  members; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  counter; int /*<<< orphan*/  size; TYPE_3__ u; int /*<<< orphan*/  struct_sizeof; int /*<<< orphan*/  type_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  members; } ;
struct TYPE_6__ {int const type; int /*<<< orphan*/  counter; int /*<<< orphan*/  size; int /*<<< orphan*/  struct_sizeof; int /*<<< orphan*/  type_name; TYPE_1__ u; } ;

/* Variables and functions */
 struct ECPGtype* ECPGmake_array_type (struct ECPGtype*,int /*<<< orphan*/ ) ; 
 struct ECPGtype* ECPGmake_simple_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECPGmake_struct_member (int /*<<< orphan*/ ,struct ECPGtype*,struct ECPGstruct_member**) ; 
 struct ECPGtype* ECPGmake_struct_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ECPGt_array 130 
#define  ECPGt_struct 129 
#define  ECPGt_union 128 

struct ECPGstruct_member *
ECPGstruct_member_dup(struct ECPGstruct_member *rm)
{
	struct ECPGstruct_member *new = NULL;

	while (rm)
	{
		struct ECPGtype *type;

		switch (rm->type->type)
		{
			case ECPGt_struct:
			case ECPGt_union:
				type = ECPGmake_struct_type(rm->type->u.members, rm->type->type, rm->type->type_name, rm->type->struct_sizeof);
				break;
			case ECPGt_array:

				/*
				 * if this array does contain a struct again, we have to
				 * create the struct too
				 */
				if (rm->type->u.element->type == ECPGt_struct || rm->type->u.element->type == ECPGt_union)
					type = ECPGmake_struct_type(rm->type->u.element->u.members, rm->type->u.element->type, rm->type->u.element->type_name, rm->type->u.element->struct_sizeof);
				else
					type = ECPGmake_array_type(ECPGmake_simple_type(rm->type->u.element->type, rm->type->u.element->size, rm->type->u.element->counter), rm->type->size);
				break;
			default:
				type = ECPGmake_simple_type(rm->type->type, rm->type->size, rm->type->counter);
				break;
		}

		ECPGmake_struct_member(rm->name, type, &new);

		rm = rm->next;
	}

	return new;
}