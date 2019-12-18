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
struct lwan_lua_priv {int /*<<< orphan*/  cache_key; int /*<<< orphan*/  cache_period; } ;
struct cache {int dummy; } ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 struct cache* cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lwan_lua_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_debug (char*) ; 
 int /*<<< orphan*/  lwan_status_error (char*) ; 
 struct cache* pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,struct cache*) ; 
 int /*<<< orphan*/  state_create ; 
 int /*<<< orphan*/  state_destroy ; 

__attribute__((used)) static struct cache *get_or_create_cache(struct lwan_lua_priv *priv)
{
    struct cache *cache = pthread_getspecific(priv->cache_key);

    if (UNLIKELY(!cache)) {
        lwan_status_debug("Creating cache for this thread");
        cache =
            cache_create(state_create, state_destroy, priv, priv->cache_period);
        if (UNLIKELY(!cache))
            lwan_status_error("Could not create cache");
        /* FIXME: This cache instance leaks: store it somewhere and
         * free it on module shutdown */
        pthread_setspecific(priv->cache_key, cache);
    }

    return cache;
}