#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int sl_curr; unsigned int perslab; } ;
typedef  TYPE_1__ slabclass_t ;

/* Variables and functions */
 scalar_t__ mem_limit ; 
 scalar_t__ mem_malloced ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* slabclass ; 
 int /*<<< orphan*/  slabs_lock ; 

unsigned int slabs_available_chunks(const unsigned int id, bool *mem_flag,
        unsigned int *chunks_perslab) {
    unsigned int ret;
    slabclass_t *p;

    pthread_mutex_lock(&slabs_lock);
    p = &slabclass[id];
    ret = p->sl_curr;
    if (mem_flag != NULL)
        *mem_flag = mem_malloced >= mem_limit ? true : false;
    if (chunks_perslab != NULL)
        *chunks_perslab = p->perslab;
    pthread_mutex_unlock(&slabs_lock);
    return ret;
}