#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int closed; scalar_t__ version; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ store_page ;
struct TYPE_5__ {TYPE_1__* pages; } ;
typedef  TYPE_2__ store_engine ;

/* Variables and functions */
 int /*<<< orphan*/  extstore_run_maint (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void extstore_close_page(void *ptr, unsigned int page_id, uint64_t page_version) {
    store_engine *e = (store_engine *)ptr;
    store_page *p = &e->pages[page_id];

    pthread_mutex_lock(&p->mutex);
    if (!p->closed && p->version == page_version) {
        p->closed = true;
        extstore_run_maint(e);
    }
    pthread_mutex_unlock(&p->mutex);
}