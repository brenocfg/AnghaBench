#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int slabs; } ;

/* Variables and functions */
 size_t SLAB_GLOBAL_PAGE_POOL ; 
 scalar_t__ mem_limit ; 
 scalar_t__ mem_malloced ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* slabclass ; 
 int /*<<< orphan*/  slabs_lock ; 

unsigned int global_page_pool_size(bool *mem_flag) {
    unsigned int ret = 0;
    pthread_mutex_lock(&slabs_lock);
    if (mem_flag != NULL)
        *mem_flag = mem_malloced >= mem_limit ? true : false;
    ret = slabclass[SLAB_GLOBAL_PAGE_POOL].slabs;
    pthread_mutex_unlock(&slabs_lock);
    return ret;
}