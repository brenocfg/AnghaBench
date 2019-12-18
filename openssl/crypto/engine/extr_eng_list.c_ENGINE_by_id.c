#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* id; int flags; int /*<<< orphan*/  struct_ref; struct TYPE_10__* next; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 char* ENGINESDIR ; 
 int ENGINE_FLAGS_BY_ID_COPY ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_BY_ID ; 
 int /*<<< orphan*/  ENGINE_R_NO_SUCH_ENGINE ; 
 int /*<<< orphan*/  ENGINE_ctrl_cmd_string (TYPE_1__*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_free (TYPE_1__*) ; 
 TYPE_1__* ENGINE_new () ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_engine_lock_init ; 
 int /*<<< orphan*/  engine_cpy (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* engine_list_head ; 
 int /*<<< orphan*/  engine_lock_init ; 
 int /*<<< orphan*/  engine_ref_debug (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  global_engine_lock ; 
 char* ossl_safe_getenv (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

ENGINE *ENGINE_by_id(const char *id)
{
    ENGINE *iterator;
    char *load_dir = NULL;
    if (id == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_BY_ID, ERR_R_PASSED_NULL_PARAMETER);
        return NULL;
    }
    if (!RUN_ONCE(&engine_lock_init, do_engine_lock_init)) {
        ENGINEerr(ENGINE_F_ENGINE_BY_ID, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    CRYPTO_THREAD_write_lock(global_engine_lock);
    iterator = engine_list_head;
    while (iterator && (strcmp(id, iterator->id) != 0))
        iterator = iterator->next;
    if (iterator != NULL) {
        /*
         * We need to return a structural reference. If this is an ENGINE
         * type that returns copies, make a duplicate - otherwise increment
         * the existing ENGINE's reference count.
         */
        if (iterator->flags & ENGINE_FLAGS_BY_ID_COPY) {
            ENGINE *cp = ENGINE_new();
            if (cp == NULL)
                iterator = NULL;
            else {
                engine_cpy(cp, iterator);
                iterator = cp;
            }
        } else {
            iterator->struct_ref++;
            engine_ref_debug(iterator, 0, 1);
        }
    }
    CRYPTO_THREAD_unlock(global_engine_lock);
    if (iterator != NULL)
        return iterator;
    /*
     * Prevent infinite recursion if we're looking for the dynamic engine.
     */
    if (strcmp(id, "dynamic")) {
        if ((load_dir = ossl_safe_getenv("OPENSSL_ENGINES")) == NULL)
            load_dir = ENGINESDIR;
        iterator = ENGINE_by_id("dynamic");
        if (!iterator || !ENGINE_ctrl_cmd_string(iterator, "ID", id, 0) ||
            !ENGINE_ctrl_cmd_string(iterator, "DIR_LOAD", "2", 0) ||
            !ENGINE_ctrl_cmd_string(iterator, "DIR_ADD",
                                    load_dir, 0) ||
            !ENGINE_ctrl_cmd_string(iterator, "LIST_ADD", "1", 0) ||
            !ENGINE_ctrl_cmd_string(iterator, "LOAD", NULL, 0))
            goto notfound;
        return iterator;
    }
 notfound:
    ENGINE_free(iterator);
    ENGINEerr(ENGINE_F_ENGINE_BY_ID, ENGINE_R_NO_SUCH_ENGINE);
    ERR_add_error_data(2, "id=", id);
    return NULL;
    /* EEK! Experimental code ends */
}