#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * v; } ;
struct TYPE_7__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ref_t ;
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  v; scalar_t__ is_const; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ dynamic_var_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REF_CONST ; 
 int /*<<< orphan*/  REF_VAR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL lookup_dynamic_vars(dynamic_var_t *var, const WCHAR *name, ref_t *ref)
{
    while(var) {
        if(!strcmpiW(var->name, name)) {
            ref->type = var->is_const ? REF_CONST : REF_VAR;
            ref->u.v = &var->v;
            return TRUE;
        }

        var = var->next;
    }

    return FALSE;
}