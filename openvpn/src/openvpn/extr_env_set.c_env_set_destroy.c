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
struct env_set {struct env_set* string; struct env_set* next; struct env_set* list; int /*<<< orphan*/ * gc; } ;
struct env_item {struct env_item* string; struct env_item* next; struct env_item* list; int /*<<< orphan*/ * gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct env_set*) ; 

void
env_set_destroy(struct env_set *es)
{
    if (es && es->gc == NULL)
    {
        struct env_item *e = es->list;
        while (e)
        {
            struct env_item *next = e->next;
            free(e->string);
            free(e);
            e = next;
        }
        free(es);
    }
}