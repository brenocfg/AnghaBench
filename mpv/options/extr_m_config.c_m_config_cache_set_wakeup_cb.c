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
struct m_config_shadow {int num_listeners; int /*<<< orphan*/  lock; struct m_config_cache** listeners; } ;
struct m_config_cache {int in_list; void (* wakeup_cb ) (void*) ;void* wakeup_cb_ctx; struct m_config_shadow* shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,struct m_config_cache**,int,struct m_config_cache*) ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct m_config_cache**,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct m_config_cache**) ; 

void m_config_cache_set_wakeup_cb(struct m_config_cache *cache,
                                  void (*cb)(void *ctx), void *cb_ctx)
{
    struct m_config_shadow *shadow = cache->shadow;

    pthread_mutex_lock(&shadow->lock);
    if (cache->in_list) {
        for (int n = 0; n < shadow->num_listeners; n++) {
            if (shadow->listeners[n] == cache) {
                MP_TARRAY_REMOVE_AT(shadow->listeners, shadow->num_listeners, n);
                break;
            }
        }
        for (int n = 0; n < shadow->num_listeners; n++)
            assert(shadow->listeners[n] != cache); // only 1 wakeup_cb per cache
        // (The deinitialization path relies on this to free all memory.)
        if (!shadow->num_listeners) {
            talloc_free(shadow->listeners);
            shadow->listeners = NULL;
        }
    }
    if (cb) {
        MP_TARRAY_APPEND(NULL, shadow->listeners, shadow->num_listeners, cache);
        cache->in_list = true;
        cache->wakeup_cb = cb;
        cache->wakeup_cb_ctx = cb_ctx;
    }
    pthread_mutex_unlock(&shadow->lock);
}