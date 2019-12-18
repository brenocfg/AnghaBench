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
struct fd_lookup_st {int del; void const* key; int add; struct fd_lookup_st* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  numdel; int /*<<< orphan*/  numadd; struct fd_lookup_st* fds; } ;
typedef  TYPE_1__ ASYNC_WAIT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (struct fd_lookup_st*) ; 

int ASYNC_WAIT_CTX_clear_fd(ASYNC_WAIT_CTX *ctx, const void *key)
{
    struct fd_lookup_st *curr, *prev;

    curr = ctx->fds;
    prev = NULL;
    while (curr != NULL) {
        if (curr->del == 1) {
            /* This one has been marked deleted already so do nothing */
            prev = curr;
            curr = curr->next;
            continue;
        }
        if (curr->key == key) {
            /* If fd has just been added, remove it from the list */
            if (curr->add == 1) {
                if (ctx->fds == curr) {
                    ctx->fds = curr->next;
                } else {
                    prev->next = curr->next;
                }

                /* It is responsibility of the caller to cleanup before calling
                 * ASYNC_WAIT_CTX_clear_fd
                 */
                OPENSSL_free(curr);
                ctx->numadd--;
                return 1;
            }

            /*
             * Mark it as deleted. We don't call cleanup if explicitly asked
             * to clear an fd. We assume the caller is going to do that (if
             * appropriate).
             */
            curr->del = 1;
            ctx->numdel++;
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}