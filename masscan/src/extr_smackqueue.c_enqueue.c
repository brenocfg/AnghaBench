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
struct Queue {struct QueueElement* m_tail; struct QueueElement* m_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

void
enqueue(struct Queue *queue, unsigned data)
{
    struct QueueElement *element;

    element = (struct QueueElement *)malloc(sizeof (struct QueueElement));
    if (element == NULL) {
        fprintf(stderr, "%s: out of memory error\n", "smack");
        exit(1);
    }

    if (queue->m_head == NULL) {
        /* If nothing in the queue, initialize the queue with the
         * first data */
        queue->m_head = element;
    } else {
        /* Else, add the data to the the tail of the queue */
        queue->m_tail->m_next = element;
    }

    element->m_data = data;
    element->m_next = NULL;
    queue->m_tail = element;
}