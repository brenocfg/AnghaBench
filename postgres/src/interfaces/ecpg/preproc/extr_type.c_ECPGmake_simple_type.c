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
struct TYPE_2__ {int /*<<< orphan*/ * element; } ;
struct ECPGtype {int type; char* size; int counter; int /*<<< orphan*/ * struct_sizeof; TYPE_1__ u; int /*<<< orphan*/ * type_name; } ;
typedef  enum ECPGttype { ____Placeholder_ECPGttype } ECPGttype ;

/* Variables and functions */
 scalar_t__ mm_alloc (int) ; 

struct ECPGtype *
ECPGmake_simple_type(enum ECPGttype type, char *size, int counter)
{
	struct ECPGtype *ne = (struct ECPGtype *) mm_alloc(sizeof(struct ECPGtype));

	ne->type = type;
	ne->type_name = NULL;
	ne->size = size;
	ne->u.element = NULL;
	ne->struct_sizeof = NULL;
	ne->counter = counter;		/* only needed for varchar and bytea */

	return ne;
}