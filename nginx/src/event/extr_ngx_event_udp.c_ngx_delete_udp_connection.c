#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* udp; TYPE_1__* listening; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_4__ {int /*<<< orphan*/  rbtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ngx_delete_udp_connection(void *data)
{
    ngx_connection_t  *c = data;

    if (c->udp == NULL) {
        return;
    }

    ngx_rbtree_delete(&c->listening->rbtree, &c->udp->node);

    c->udp = NULL;
}