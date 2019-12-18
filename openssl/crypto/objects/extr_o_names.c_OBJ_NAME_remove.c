#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* free_func ) (char const*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {char const* name; int type; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int OBJ_NAME_ALIAS ; 
 int /*<<< orphan*/  OBJ_NAME_init () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* lh_OBJ_NAME_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * name_funcs_stack ; 
 int /*<<< orphan*/  names_lh ; 
 int /*<<< orphan*/  obj_lock ; 
 scalar_t__ sk_NAME_FUNCS_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_NAME_FUNCS_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (char const*,scalar_t__,int /*<<< orphan*/ ) ; 

int OBJ_NAME_remove(const char *name, int type)
{
    OBJ_NAME on, *ret;
    int ok = 0;

    if (!OBJ_NAME_init())
        return 0;

    CRYPTO_THREAD_write_lock(obj_lock);

    type &= ~OBJ_NAME_ALIAS;
    on.name = name;
    on.type = type;
    ret = lh_OBJ_NAME_delete(names_lh, &on);
    if (ret != NULL) {
        /* free things */
        if ((name_funcs_stack != NULL)
            && (sk_NAME_FUNCS_num(name_funcs_stack) > ret->type)) {
            /*
             * XXX: I'm not sure I understand why the free function should
             * get three arguments... -- Richard Levitte
             */
            sk_NAME_FUNCS_value(name_funcs_stack,
                                ret->type)->free_func(ret->name, ret->type,
                                                      ret->data);
        }
        OPENSSL_free(ret);
        ok = 1;
    }

    CRYPTO_THREAD_unlock(obj_lock);
    return ok;
}