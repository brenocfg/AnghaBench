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
struct TYPE_6__ {struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_F_ENGINE_LIST_REMOVE ; 
 int /*<<< orphan*/  ENGINE_R_ENGINE_IS_NOT_IN_LIST ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  engine_free_util (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* engine_list_head ; 
 TYPE_1__* engine_list_tail ; 

__attribute__((used)) static int engine_list_remove(ENGINE *e)
{
    ENGINE *iterator;

    if (e == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_LIST_REMOVE, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    /* We need to check that e is in our linked list! */
    iterator = engine_list_head;
    while (iterator && (iterator != e))
        iterator = iterator->next;
    if (iterator == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_LIST_REMOVE,
                  ENGINE_R_ENGINE_IS_NOT_IN_LIST);
        return 0;
    }
    /* un-link e from the chain. */
    if (e->next)
        e->next->prev = e->prev;
    if (e->prev)
        e->prev->next = e->next;
    /* Correct our head/tail if necessary. */
    if (engine_list_head == e)
        engine_list_head = e->next;
    if (engine_list_tail == e)
        engine_list_tail = e->prev;
    engine_free_util(e, 0);
    return 1;
}