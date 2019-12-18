#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* flags; TYPE_3__* multi_head; } ;
typedef  TYPE_2__ redisCluster ;
struct TYPE_11__ {struct TYPE_11__* next; int /*<<< orphan*/  slot; } ;
typedef  TYPE_3__ clusterFoldItem ;
struct TYPE_12__ {scalar_t__ mode; scalar_t__ watching; } ;
struct TYPE_9__ {void* mode; } ;

/* Variables and functions */
 void* ATOMIC ; 
 scalar_t__ MULTI ; 
 TYPE_7__* SLOT_SOCK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cluster_disconnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ cluster_send_discard (TYPE_2__*,int /*<<< orphan*/ ) ; 

int cluster_abort_exec(redisCluster *c) {
    clusterFoldItem *fi = c->multi_head;

    /* Loop through our fold items */
    while (fi) {
        if (SLOT_SOCK(c,fi->slot)->mode == MULTI) {
            if (cluster_send_discard(c, fi->slot) < 0) {
                cluster_disconnect(c, 0);
                return -1;
            }
            SLOT_SOCK(c,fi->slot)->mode = ATOMIC;
            SLOT_SOCK(c,fi->slot)->watching = 0;
        }
        fi = fi->next;
    }

    /* Update our overall cluster state */
    c->flags->mode = ATOMIC;

    /* Success */
    return 0;
}