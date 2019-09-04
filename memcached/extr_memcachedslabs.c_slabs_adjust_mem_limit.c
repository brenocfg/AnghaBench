#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int do_slabs_adjust_mem_limit (size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slabs_lock ; 

bool slabs_adjust_mem_limit(size_t new_mem_limit) {
    bool ret;
    pthread_mutex_lock(&slabs_lock);
    ret = do_slabs_adjust_mem_limit(new_mem_limit);
    pthread_mutex_unlock(&slabs_lock);
    return ret;
}