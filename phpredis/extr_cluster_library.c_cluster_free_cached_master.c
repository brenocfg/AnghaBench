#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {size_t slaves; TYPE_3__* slot; TYPE_3__* slave; TYPE_1__ host; } ;
typedef  TYPE_2__ redisCachedMaster ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pefree (TYPE_3__*,int) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cluster_free_cached_master(redisCachedMaster *cm) {
    size_t i;

    /* Free each slave entry */
    for (i = 0; i < cm->slaves; i++) {
        zend_string_release(cm->slave[i].addr);
    }

    /* Free other elements */
    zend_string_release(cm->host.addr);
    pefree(cm->slave, 1);
    pefree(cm->slot, 1);
}