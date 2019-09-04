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
struct QueueElement {unsigned int m_data; struct QueueElement* m_next; } ;
struct Queue {struct QueueElement* m_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct QueueElement*) ; 

unsigned
dequeue(struct Queue *queue)
{
    if (queue->m_head == NULL)
        return 0;
    else {
        struct QueueElement *element;
        unsigned result;

        element = queue->m_head;
        result = element->m_data;
        queue->m_head = element->m_next;

        free(element);
        return result;
    }
}