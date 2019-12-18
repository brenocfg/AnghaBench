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
typedef  int /*<<< orphan*/  uint8_t ;
struct gc_entry {struct gc_entry* next; } ;
struct gc_arena {struct gc_entry* list; } ;
struct buffer {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct buffer) ; 
 int /*<<< orphan*/  free (struct gc_entry*) ; 

__attribute__((used)) static void
free_buf_gc(struct buffer *buf, struct gc_arena *gc)
{
    if (gc)
    {
        struct gc_entry **e = &gc->list;

        while (*e)
        {
            /* check if this object is the one we want to delete */
            if ((uint8_t *)(*e + 1) == buf->data)
            {
                struct gc_entry *to_delete = *e;

                /* remove element from linked list and free it */
                *e = (*e)->next;
                free(to_delete);

                break;
            }

            e = &(*e)->next;
        }
    }

    CLEAR(*buf);
}