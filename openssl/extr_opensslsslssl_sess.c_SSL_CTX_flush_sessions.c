#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * sessions; } ;
struct TYPE_5__ {long time; int /*<<< orphan*/ * cache; TYPE_2__* ctx; } ;
typedef  TYPE_1__ TIMEOUT_PARAM ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_SSL_SESSION_doall_TIMEOUT_PARAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 unsigned long lh_SSL_SESSION_get_down_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_SSL_SESSION_set_down_load (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timeout_cb ; 

void SSL_CTX_flush_sessions(SSL_CTX *s, long t)
{
    unsigned long i;
    TIMEOUT_PARAM tp;

    tp.ctx = s;
    tp.cache = s->sessions;
    if (tp.cache == NULL)
        return;
    tp.time = t;
    CRYPTO_THREAD_write_lock(s->lock);
    i = lh_SSL_SESSION_get_down_load(s->sessions);
    lh_SSL_SESSION_set_down_load(s->sessions, 0);
    lh_SSL_SESSION_doall_TIMEOUT_PARAM(tp.cache, timeout_cb, &tp);
    lh_SSL_SESSION_set_down_load(s->sessions, i);
    CRYPTO_THREAD_unlock(s->lock);
}