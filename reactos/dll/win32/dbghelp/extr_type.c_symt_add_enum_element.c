#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tag; } ;
struct symt_enum {int /*<<< orphan*/  vchildren; int /*<<< orphan*/  base_type; TYPE_2__ symt; } ;
struct symt {int /*<<< orphan*/  tag; } ;
struct TYPE_10__ {int lVal; } ;
struct TYPE_11__ {TYPE_3__ n3; int /*<<< orphan*/  vt; } ;
struct TYPE_12__ {TYPE_4__ n2; } ;
struct TYPE_13__ {TYPE_5__ n1; } ;
struct TYPE_14__ {TYPE_6__ value; } ;
struct TYPE_8__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  name; } ;
struct symt_data {struct symt symt; TYPE_7__ u; int /*<<< orphan*/  type; TYPE_2__* container; int /*<<< orphan*/  kind; TYPE_1__ hash_elt; } ;
struct module {int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DataIsConstant ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SymTagData ; 
 scalar_t__ SymTagEnum ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  assert (int) ; 
 struct symt_data* pool_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 struct symt** vector_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL symt_add_enum_element(struct module* module, struct symt_enum* enum_type,
                           const char* name, int value)
{
    struct symt_data*   e;
    struct symt**       p;

    assert(enum_type->symt.tag == SymTagEnum);
    e = pool_alloc(&module->pool, sizeof(*e));
    if (e == NULL) return FALSE;

    e->symt.tag = SymTagData;
    e->hash_elt.name = pool_strdup(&module->pool, name);
    e->hash_elt.next = NULL;
    e->kind = DataIsConstant;
    e->container = &enum_type->symt;
    e->type = enum_type->base_type;
    e->u.value.n1.n2.vt = VT_I4;
    e->u.value.n1.n2.n3.lVal = value;

    p = vector_add(&enum_type->vchildren, &module->pool);
    if (!p) return FALSE; /* FIXME we leak e */
    *p = &e->symt;

    return TRUE;
}