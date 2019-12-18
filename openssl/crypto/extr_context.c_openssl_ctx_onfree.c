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
struct openssl_ctx_onfree_list_st {struct openssl_ctx_onfree_list_st* next; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  openssl_ctx_onfree_fn ;
struct TYPE_3__ {struct openssl_ctx_onfree_list_st* onfreelist; } ;
typedef  TYPE_1__ OPENSSL_CTX ;

/* Variables and functions */
 struct openssl_ctx_onfree_list_st* OPENSSL_malloc (int) ; 

int openssl_ctx_onfree(OPENSSL_CTX *ctx, openssl_ctx_onfree_fn onfreefn)
{
    struct openssl_ctx_onfree_list_st *newonfree
        = OPENSSL_malloc(sizeof(*newonfree));

    if (newonfree == NULL)
        return 0;

    newonfree->fn = onfreefn;
    newonfree->next = ctx->onfreelist;
    ctx->onfreelist = newonfree;

    return 1;
}