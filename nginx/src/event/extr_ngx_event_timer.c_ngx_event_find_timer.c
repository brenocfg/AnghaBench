#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ key; } ;
typedef  TYPE_1__ ngx_rbtree_node_t ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  scalar_t__ ngx_msec_int_t ;
struct TYPE_8__ {TYPE_1__* sentinel; TYPE_1__* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_TIMER_INFINITE ; 
 scalar_t__ ngx_current_msec ; 
 TYPE_6__ ngx_event_timer_rbtree ; 
 TYPE_1__ ngx_event_timer_sentinel ; 
 TYPE_1__* ngx_rbtree_min (TYPE_1__*,TYPE_1__*) ; 

ngx_msec_t
ngx_event_find_timer(void)
{
    ngx_msec_int_t      timer;
    ngx_rbtree_node_t  *node, *root, *sentinel;

    if (ngx_event_timer_rbtree.root == &ngx_event_timer_sentinel) {
        return NGX_TIMER_INFINITE;
    }

    root = ngx_event_timer_rbtree.root;
    sentinel = ngx_event_timer_rbtree.sentinel;

    node = ngx_rbtree_min(root, sentinel);

    timer = (ngx_msec_int_t) (node->key - ngx_current_msec);

    return (ngx_msec_t) (timer > 0 ? timer : 0);
}