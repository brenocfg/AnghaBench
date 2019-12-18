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
struct buffer_list {scalar_t__ size; int /*<<< orphan*/ * tail; struct buffer_entry* head; } ;
struct buffer_entry {int /*<<< orphan*/  buf; struct buffer_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct buffer_entry*) ; 
 int /*<<< orphan*/  free_buf (int /*<<< orphan*/ *) ; 

void
buffer_list_reset(struct buffer_list *ol)
{
    struct buffer_entry *e = ol->head;
    while (e)
    {
        struct buffer_entry *next = e->next;
        free_buf(&e->buf);
        free(e);
        e = next;
    }
    ol->head = ol->tail = NULL;
    ol->size = 0;
}