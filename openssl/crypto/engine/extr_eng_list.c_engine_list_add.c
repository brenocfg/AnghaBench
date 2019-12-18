#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  struct_ref; struct TYPE_6__* prev; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_F_ENGINE_LIST_ADD ; 
 int /*<<< orphan*/  ENGINE_R_CONFLICTING_ENGINE_ID ; 
 int /*<<< orphan*/  ENGINE_R_INTERNAL_LIST_ERROR ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  engine_cleanup_add_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_list_cleanup ; 
 TYPE_1__* engine_list_head ; 
 TYPE_1__* engine_list_tail ; 
 int /*<<< orphan*/  engine_ref_debug (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int engine_list_add(ENGINE *e)
{
    int conflict = 0;
    ENGINE *iterator = NULL;

    if (e == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_LIST_ADD, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    iterator = engine_list_head;
    while (iterator && !conflict) {
        conflict = (strcmp(iterator->id, e->id) == 0);
        iterator = iterator->next;
    }
    if (conflict) {
        ENGINEerr(ENGINE_F_ENGINE_LIST_ADD, ENGINE_R_CONFLICTING_ENGINE_ID);
        return 0;
    }
    if (engine_list_head == NULL) {
        /* We are adding to an empty list. */
        if (engine_list_tail) {
            ENGINEerr(ENGINE_F_ENGINE_LIST_ADD, ENGINE_R_INTERNAL_LIST_ERROR);
            return 0;
        }
        engine_list_head = e;
        e->prev = NULL;
        /*
         * The first time the list allocates, we should register the cleanup.
         */
        engine_cleanup_add_last(engine_list_cleanup);
    } else {
        /* We are adding to the tail of an existing list. */
        if ((engine_list_tail == NULL) || (engine_list_tail->next != NULL)) {
            ENGINEerr(ENGINE_F_ENGINE_LIST_ADD, ENGINE_R_INTERNAL_LIST_ERROR);
            return 0;
        }
        engine_list_tail->next = e;
        e->prev = engine_list_tail;
    }
    /*
     * Having the engine in the list assumes a structural reference.
     */
    e->struct_ref++;
    engine_ref_debug(e, 0, 1);
    /* However it came to be, e is the last item in the list. */
    engine_list_tail = e;
    e->next = NULL;
    return 1;
}