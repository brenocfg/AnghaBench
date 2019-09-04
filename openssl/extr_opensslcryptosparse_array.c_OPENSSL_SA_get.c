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
typedef  int ossl_uintmax_t ;
struct TYPE_3__ {int top; void** nodes; int levels; } ;
typedef  TYPE_1__ OPENSSL_SA ;

/* Variables and functions */
 int OPENSSL_SA_BLOCK_BITS ; 
 int SA_BLOCK_MASK ; 

void *OPENSSL_SA_get(const OPENSSL_SA *sa, ossl_uintmax_t n)
{
    int level;
    void **p, *r = NULL;

    if (sa == NULL)
        return NULL;

    if (n <= sa->top) {
        p = sa->nodes;
        for (level = sa->levels - 1; p != NULL && level > 0; level--)
            p = (void **)p[(n >> (OPENSSL_SA_BLOCK_BITS * level))
                           & SA_BLOCK_MASK];
        r = p == NULL ? NULL : p[n & SA_BLOCK_MASK];
    }
    return r;
}