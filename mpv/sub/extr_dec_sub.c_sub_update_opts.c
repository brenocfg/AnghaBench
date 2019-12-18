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
struct dec_sub {int /*<<< orphan*/  lock; int /*<<< orphan*/  opts_cache; } ;

/* Variables and functions */
 scalar_t__ m_config_cache_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_subtitle_speed (struct dec_sub*) ; 

void sub_update_opts(struct dec_sub *sub)
{
    pthread_mutex_lock(&sub->lock);
    if (m_config_cache_update(sub->opts_cache))
        update_subtitle_speed(sub);
    pthread_mutex_unlock(&sub->lock);
}