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
typedef  scalar_t__ uint64_t ;
struct vo_internal {int /*<<< orphan*/  lock; scalar_t__ timing_offset; } ;
struct vo {TYPE_1__* opts; struct vo_internal* in; } ;
struct TYPE_2__ {int timing_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_opts(struct vo *vo)
{
    struct vo_internal *in = vo->in;

    pthread_mutex_lock(&in->lock);
    in->timing_offset = (uint64_t)(vo->opts->timing_offset * 1e6);
    pthread_mutex_unlock(&in->lock);
}