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
struct list_node {struct list_node const* prev; struct list_node* next; } ;

/* Variables and functions */
 struct list_node* corrupt (char const*,struct list_node const*,struct list_node const*,unsigned int) ; 

struct list_node *list_check_node(const struct list_node *node,
                                  const char *abortstr)
{
    const struct list_node *p, *n;
    unsigned int count = 0;

    for (p = node, n = node->next; n != node; p = n, n = n->next) {
        count++;
        if (n->prev != p)
            return corrupt(abortstr, node, n, count);
    }
    /* Check prev on head node. */
    if (node->prev != p)
        return corrupt(abortstr, node, node, 0);

    return (struct list_node *)node;
}