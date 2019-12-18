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
typedef  int /*<<< orphan*/  (* match_fn_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_4__ {int /*<<< orphan*/ * data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ list_item_t ;
typedef  int /*<<< orphan*/ * LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static LPVOID
RemoveListItem(list_item_t **pfirst, match_fn_t match, LPVOID ctx)
{
    LPVOID data = NULL;
    list_item_t **pnext;

    for (pnext = pfirst; *pnext; pnext = &(*pnext)->next)
    {
        list_item_t *item = *pnext;
        if (!match(item->data, ctx))
        {
            continue;
        }

        /* Found item, remove from the list and free memory */
        *pnext = item->next;
        data = item->data;
        free(item);
        break;
    }
    return data;
}