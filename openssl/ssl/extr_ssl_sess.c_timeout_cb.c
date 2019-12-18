#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  (* remove_session_cb ) (TYPE_5__*,TYPE_2__*) ;} ;
struct TYPE_12__ {scalar_t__ time; scalar_t__ timeout; int not_resumable; } ;
struct TYPE_11__ {scalar_t__ time; TYPE_5__* ctx; int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ TIMEOUT_PARAM ;
typedef  TYPE_2__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_SESSION_free (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_SESSION_list_remove (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lh_SSL_SESSION_delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_2__*) ; 

__attribute__((used)) static void timeout_cb(SSL_SESSION *s, TIMEOUT_PARAM *p)
{
    if ((p->time == 0) || (p->time > (s->time + s->timeout))) { /* timeout */
        /*
         * The reason we don't call SSL_CTX_remove_session() is to save on
         * locking overhead
         */
        (void)lh_SSL_SESSION_delete(p->cache, s);
        SSL_SESSION_list_remove(p->ctx, s);
        s->not_resumable = 1;
        if (p->ctx->remove_session_cb != NULL)
            p->ctx->remove_session_cb(p->ctx, s);
        SSL_SESSION_free(s);
    }
}