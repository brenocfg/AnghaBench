#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* Y; void* X; } ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  type; TYPE_1__ pt; } ;
typedef  TYPE_2__ path_list_node_t ;
typedef  void* REAL ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_2__* heap_alloc_zero (int) ; 

__attribute__((used)) static path_list_node_t* add_path_list_node(path_list_node_t *node, REAL x, REAL y, BOOL type)
{
    path_list_node_t *new;

    new = heap_alloc_zero(sizeof(path_list_node_t));
    if(!new)
        return NULL;

    new->pt.X  = x;
    new->pt.Y  = y;
    new->type  = type;
    new->next  = node->next;
    node->next = new;

    return new;
}