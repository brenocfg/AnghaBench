#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ pair_t ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_2__ list_t ;
struct TYPE_10__ {TYPE_2__ list; } ;
typedef  TYPE_3__ hashtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonp_free (TYPE_1__*) ; 
 TYPE_1__* list_to_pair (TYPE_2__*) ; 

__attribute__((used)) static void hashtable_do_clear(hashtable_t *hashtable)
{
    list_t *list, *next;
    pair_t *pair;

    for(list = hashtable->list.next; list != &hashtable->list; list = next)
    {
        next = list->next;
        pair = list_to_pair(list);
        json_decref(pair->value);
        jsonp_free(pair);
    }
}