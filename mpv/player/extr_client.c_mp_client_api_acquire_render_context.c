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
struct mpv_render_context {int dummy; } ;
struct mp_client_api {int /*<<< orphan*/  lock; struct mpv_render_context* render_context; } ;

/* Variables and functions */
 scalar_t__ mp_render_context_acquire (struct mpv_render_context*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct mpv_render_context *
mp_client_api_acquire_render_context(struct mp_client_api *ca)
{
    struct mpv_render_context *res = NULL;
    pthread_mutex_lock(&ca->lock);
    if (ca->render_context && mp_render_context_acquire(ca->render_context))
        res = ca->render_context;
    pthread_mutex_unlock(&ca->lock);
    return res;
}