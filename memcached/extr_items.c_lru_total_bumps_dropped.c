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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; scalar_t__ dropped; struct TYPE_3__* next; } ;
typedef  TYPE_1__ lru_bump_buf ;

/* Variables and functions */
 TYPE_1__* bump_buf_head ; 
 int /*<<< orphan*/  bump_buf_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t lru_total_bumps_dropped(void) {
    uint64_t total = 0;
    lru_bump_buf *b;
    pthread_mutex_lock(&bump_buf_lock);
    for (b = bump_buf_head; b != NULL; b=b->next) {
        pthread_mutex_lock(&b->mutex);
        total += b->dropped;
        pthread_mutex_unlock(&b->mutex);
    }
    pthread_mutex_unlock(&bump_buf_lock);
    return total;
}