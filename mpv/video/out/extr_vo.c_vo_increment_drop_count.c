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
struct vo {TYPE_1__* in; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  drop_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void vo_increment_drop_count(struct vo *vo, int64_t n)
{
    pthread_mutex_lock(&vo->in->lock);
    vo->in->drop_count += n;
    pthread_mutex_unlock(&vo->in->lock);
}