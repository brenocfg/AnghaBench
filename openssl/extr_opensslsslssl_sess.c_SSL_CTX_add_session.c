#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sess_cache_full; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__ stats; int /*<<< orphan*/  session_cache_tail; int /*<<< orphan*/  sessions; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ SSL_CTX_sess_get_cache_size (TYPE_2__*) ; 
 scalar_t__ SSL_CTX_sess_number (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_list_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_list_remove (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_SESSION_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lh_SSL_SESSION_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lh_SSL_SESSION_retrieve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_session_lock (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsan_counter (int /*<<< orphan*/ *) ; 

int SSL_CTX_add_session(SSL_CTX *ctx, SSL_SESSION *c)
{
    int ret = 0;
    SSL_SESSION *s;

    /*
     * add just 1 reference count for the SSL_CTX's session cache even though
     * it has two ways of access: each session is in a doubly linked list and
     * an lhash
     */
    SSL_SESSION_up_ref(c);
    /*
     * if session c is in already in cache, we take back the increment later
     */

    CRYPTO_THREAD_write_lock(ctx->lock);
    s = lh_SSL_SESSION_insert(ctx->sessions, c);

    /*
     * s != NULL iff we already had a session with the given PID. In this
     * case, s == c should hold (then we did not really modify
     * ctx->sessions), or we're in trouble.
     */
    if (s != NULL && s != c) {
        /* We *are* in trouble ... */
        SSL_SESSION_list_remove(ctx, s);
        SSL_SESSION_free(s);
        /*
         * ... so pretend the other session did not exist in cache (we cannot
         * handle two SSL_SESSION structures with identical session ID in the
         * same cache, which could happen e.g. when two threads concurrently
         * obtain the same session from an external cache)
         */
        s = NULL;
    } else if (s == NULL &&
               lh_SSL_SESSION_retrieve(ctx->sessions, c) == NULL) {
        /* s == NULL can also mean OOM error in lh_SSL_SESSION_insert ... */

        /*
         * ... so take back the extra reference and also don't add
         * the session to the SSL_SESSION_list at this time
         */
        s = c;
    }

    /* Put at the head of the queue unless it is already in the cache */
    if (s == NULL)
        SSL_SESSION_list_add(ctx, c);

    if (s != NULL) {
        /*
         * existing cache entry -- decrement previously incremented reference
         * count because it already takes into account the cache
         */

        SSL_SESSION_free(s);    /* s == c */
        ret = 0;
    } else {
        /*
         * new cache entry -- remove old ones if cache has become too large
         */

        ret = 1;

        if (SSL_CTX_sess_get_cache_size(ctx) > 0) {
            while (SSL_CTX_sess_number(ctx) > SSL_CTX_sess_get_cache_size(ctx)) {
                if (!remove_session_lock(ctx, ctx->session_cache_tail, 0))
                    break;
                else
                    tsan_counter(&ctx->stats.sess_cache_full);
            }
        }
    }
    CRYPTO_THREAD_unlock(ctx->lock);
    return ret;
}