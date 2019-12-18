#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ version; unsigned int bytes_used; unsigned int obj_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  closed; } ;
typedef  TYPE_2__ store_page ;
struct TYPE_7__ {unsigned int bytes_used; unsigned int objects_used; } ;
struct TYPE_9__ {TYPE_1__ stats; TYPE_2__* pages; } ;
typedef  TYPE_3__ store_engine ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_L (TYPE_3__*) ; 
 int /*<<< orphan*/  STAT_UL (TYPE_3__*) ; 
 int /*<<< orphan*/  extstore_run_maint (TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int extstore_delete(void *ptr, unsigned int page_id, uint64_t page_version,
        unsigned int count, unsigned int bytes) {
    store_engine *e = (store_engine *)ptr;
    // FIXME: validate page_id in bounds
    store_page *p = &e->pages[page_id];
    int ret = 0;

    pthread_mutex_lock(&p->mutex);
    if (!p->closed && p->version == page_version) {
        if (p->bytes_used >= bytes) {
            p->bytes_used -= bytes;
        } else {
            p->bytes_used = 0;
        }

        if (p->obj_count >= count) {
            p->obj_count -= count;
        } else {
            p->obj_count = 0; // caller has bad accounting?
        }
        STAT_L(e);
        e->stats.bytes_used -= bytes;
        e->stats.objects_used -= count;
        STAT_UL(e);

        if (p->obj_count == 0) {
            extstore_run_maint(e);
        }
    } else {
        ret = -1;
    }
    pthread_mutex_unlock(&p->mutex);
    return ret;
}