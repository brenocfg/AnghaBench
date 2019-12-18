#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* name; int type; char* data; scalar_t__ alias; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int OBJ_NAME_ALIAS ; 
 int /*<<< orphan*/  OBJ_NAME_init () ; 
 TYPE_1__* lh_OBJ_NAME_retrieve (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  names_lh ; 
 int /*<<< orphan*/  obj_lock ; 

const char *OBJ_NAME_get(const char *name, int type)
{
    OBJ_NAME on, *ret;
    int num = 0, alias;
    const char *value = NULL;

    if (name == NULL)
        return NULL;
    if (!OBJ_NAME_init())
        return NULL;
    CRYPTO_THREAD_read_lock(obj_lock);

    alias = type & OBJ_NAME_ALIAS;
    type &= ~OBJ_NAME_ALIAS;

    on.name = name;
    on.type = type;

    for (;;) {
        ret = lh_OBJ_NAME_retrieve(names_lh, &on);
        if (ret == NULL)
            break;
        if ((ret->alias) && !alias) {
            if (++num > 10)
                break;
            on.name = ret->data;
        } else {
            value = ret->data;
            break;
        }
    }

    CRYPTO_THREAD_unlock(obj_lock);
    return value;
}