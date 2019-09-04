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
typedef  enum reassign_result_type { ____Placeholder_reassign_result_type } reassign_result_type ;

/* Variables and functions */
 int REASSIGN_RUNNING ; 
 int do_slabs_reassign (int,int) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slabs_rebalance_lock ; 

enum reassign_result_type slabs_reassign(int src, int dst) {
    enum reassign_result_type ret;
    if (pthread_mutex_trylock(&slabs_rebalance_lock) != 0) {
        return REASSIGN_RUNNING;
    }
    ret = do_slabs_reassign(src, dst);
    pthread_mutex_unlock(&slabs_rebalance_lock);
    return ret;
}