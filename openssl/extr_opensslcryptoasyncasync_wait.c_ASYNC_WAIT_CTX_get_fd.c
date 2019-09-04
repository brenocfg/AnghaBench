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
struct fd_lookup_st {void const* key; struct fd_lookup_st* next; void* custom_data; int /*<<< orphan*/  fd; scalar_t__ del; } ;
struct TYPE_3__ {struct fd_lookup_st* fds; } ;
typedef  int /*<<< orphan*/  OSSL_ASYNC_FD ;
typedef  TYPE_1__ ASYNC_WAIT_CTX ;

/* Variables and functions */

int ASYNC_WAIT_CTX_get_fd(ASYNC_WAIT_CTX *ctx, const void *key,
                          OSSL_ASYNC_FD *fd, void **custom_data)
{
    struct fd_lookup_st *curr;

    curr = ctx->fds;
    while (curr != NULL) {
        if (curr->del) {
            /* This one has been marked deleted so do nothing */
            curr = curr->next;
            continue;
        }
        if (curr->key == key) {
            *fd = curr->fd;
            *custom_data = curr->custom_data;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}