#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* Y; void* X; } ;
struct TYPE_6__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  type; TYPE_1__ pt; } ;
typedef  TYPE_2__ path_list_node_t ;
typedef  void* REAL ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PathPointTypeStart ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* heap_alloc_zero (int) ; 

__attribute__((used)) static BOOL init_path_list(path_list_node_t **node, REAL x, REAL y)
{
    *node = heap_alloc_zero(sizeof(path_list_node_t));
    if(!*node)
        return FALSE;

    (*node)->pt.X = x;
    (*node)->pt.Y = y;
    (*node)->type = PathPointTypeStart;
    (*node)->next = NULL;

    return TRUE;
}