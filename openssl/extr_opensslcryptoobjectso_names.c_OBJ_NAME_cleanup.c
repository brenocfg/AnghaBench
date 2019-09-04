#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int free_type ; 
 int /*<<< orphan*/  lh_OBJ_NAME_doall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_OBJ_NAME_free (int /*<<< orphan*/ *) ; 
 unsigned long lh_OBJ_NAME_get_down_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_OBJ_NAME_set_down_load (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  name_funcs_free ; 
 int /*<<< orphan*/ * name_funcs_stack ; 
 int /*<<< orphan*/ * names_lh ; 
 int /*<<< orphan*/  names_lh_free_doall ; 
 int /*<<< orphan*/ * obj_lock ; 
 int /*<<< orphan*/  sk_NAME_FUNCS_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void OBJ_NAME_cleanup(int type)
{
    unsigned long down_load;

    if (names_lh == NULL)
        return;

    free_type = type;
    down_load = lh_OBJ_NAME_get_down_load(names_lh);
    lh_OBJ_NAME_set_down_load(names_lh, 0);

    lh_OBJ_NAME_doall(names_lh, names_lh_free_doall);
    if (type < 0) {
        lh_OBJ_NAME_free(names_lh);
        sk_NAME_FUNCS_pop_free(name_funcs_stack, name_funcs_free);
        CRYPTO_THREAD_lock_free(obj_lock);
        names_lh = NULL;
        name_funcs_stack = NULL;
        obj_lock = NULL;
    } else
        lh_OBJ_NAME_set_down_load(names_lh, down_load);
}