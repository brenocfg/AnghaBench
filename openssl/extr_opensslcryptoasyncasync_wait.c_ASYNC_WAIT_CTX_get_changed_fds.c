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
struct fd_lookup_st {struct fd_lookup_st* next; int /*<<< orphan*/  fd; scalar_t__ del; scalar_t__ add; } ;
struct TYPE_3__ {size_t numadd; size_t numdel; struct fd_lookup_st* fds; } ;
typedef  int /*<<< orphan*/  OSSL_ASYNC_FD ;
typedef  TYPE_1__ ASYNC_WAIT_CTX ;

/* Variables and functions */

int ASYNC_WAIT_CTX_get_changed_fds(ASYNC_WAIT_CTX *ctx, OSSL_ASYNC_FD *addfd,
                                   size_t *numaddfds, OSSL_ASYNC_FD *delfd,
                                   size_t *numdelfds)
{
    struct fd_lookup_st *curr;

    *numaddfds = ctx->numadd;
    *numdelfds = ctx->numdel;
    if (addfd == NULL && delfd == NULL)
        return 1;

    curr = ctx->fds;

    while (curr != NULL) {
        /* We ignore fds that have been marked as both added and deleted */
        if (curr->del && !curr->add && (delfd != NULL)) {
            *delfd = curr->fd;
            delfd++;
        }
        if (curr->add && !curr->del && (addfd != NULL)) {
            *addfd = curr->fd;
            addfd++;
        }
        curr = curr->next;
    }

    return 1;
}