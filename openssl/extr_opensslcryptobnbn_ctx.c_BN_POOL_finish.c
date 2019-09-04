#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; TYPE_2__* vals; } ;
struct TYPE_7__ {scalar_t__ d; } ;
struct TYPE_6__ {TYPE_3__* current; TYPE_3__* head; } ;
typedef  TYPE_1__ BN_POOL ;
typedef  TYPE_2__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_POOL_SIZE ; 
 int /*<<< orphan*/  BN_clear_free (TYPE_2__*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_3__*) ; 

__attribute__((used)) static void BN_POOL_finish(BN_POOL *p)
{
    unsigned int loop;
    BIGNUM *bn;

    while (p->head) {
        for (loop = 0, bn = p->head->vals; loop++ < BN_CTX_POOL_SIZE; bn++)
            if (bn->d)
                BN_clear_free(bn);
        p->current = p->head->next;
        OPENSSL_free(p->head);
        p->head = p->current;
    }
}