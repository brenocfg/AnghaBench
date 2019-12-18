#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ num; int num_alloc; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  (* OPENSSL_sk_freefunc ) (void*) ;
typedef  int /*<<< orphan*/ * (* OPENSSL_sk_copyfunc ) (int /*<<< orphan*/ *) ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_SK_DEEP_COPY ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  OPENSSL_sk_free (TYPE_1__*) ; 
 int /*<<< orphan*/ ** OPENSSL_zalloc (int) ; 
 scalar_t__ min_nodes ; 

OPENSSL_STACK *OPENSSL_sk_deep_copy(const OPENSSL_STACK *sk,
                             OPENSSL_sk_copyfunc copy_func,
                             OPENSSL_sk_freefunc free_func)
{
    OPENSSL_STACK *ret;
    int i;

    if ((ret = OPENSSL_malloc(sizeof(*ret))) == NULL) {
        CRYPTOerr(CRYPTO_F_OPENSSL_SK_DEEP_COPY, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    /* direct structure assignment */
    *ret = *sk;

    if (sk->num == 0) {
        /* postpone |ret| data allocation */
        ret->data = NULL;
        ret->num_alloc = 0;
        return ret;
    }

    ret->num_alloc = sk->num > min_nodes ? sk->num : min_nodes;
    ret->data = OPENSSL_zalloc(sizeof(*ret->data) * ret->num_alloc);
    if (ret->data == NULL) {
        OPENSSL_free(ret);
        return NULL;
    }

    for (i = 0; i < ret->num; ++i) {
        if (sk->data[i] == NULL)
            continue;
        if ((ret->data[i] = copy_func(sk->data[i])) == NULL) {
            while (--i >= 0)
                if (ret->data[i] != NULL)
                    free_func((void *)ret->data[i]);
            OPENSSL_sk_free(ret);
            return NULL;
        }
    }
    return ret;
}