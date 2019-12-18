#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ version; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ store_page ;
struct TYPE_4__ {TYPE_1__* pages; } ;
typedef  TYPE_2__ store_engine ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int extstore_check(void *ptr, unsigned int page_id, uint64_t page_version) {
    store_engine *e = (store_engine *)ptr;
    store_page *p = &e->pages[page_id];
    int ret = 0;

    pthread_mutex_lock(&p->mutex);
    if (p->version != page_version)
        ret = -1;
    pthread_mutex_unlock(&p->mutex);
    return ret;
}