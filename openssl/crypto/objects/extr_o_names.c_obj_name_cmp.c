#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* cmp_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/ * name_funcs_stack ; 
 scalar_t__ sk_NAME_FUNCS_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_NAME_FUNCS_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int obj_name_cmp(const OBJ_NAME *a, const OBJ_NAME *b)
{
    int ret;

    ret = a->type - b->type;
    if (ret == 0) {
        if ((name_funcs_stack != NULL)
            && (sk_NAME_FUNCS_num(name_funcs_stack) > a->type)) {
            ret = sk_NAME_FUNCS_value(name_funcs_stack,
                                      a->type)->cmp_func(a->name, b->name);
        } else
            ret = strcasecmp(a->name, b->name);
    }
    return ret;
}