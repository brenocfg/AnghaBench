#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int used; TYPE_1__* current; } ;
struct TYPE_4__ {struct TYPE_4__* prev; scalar_t__ vals; } ;
typedef  TYPE_2__ BN_POOL ;

/* Variables and functions */
 int BN_CTX_POOL_SIZE ; 
 int /*<<< orphan*/  bn_check_top (scalar_t__) ; 

__attribute__((used)) static void BN_POOL_release(BN_POOL *p, unsigned int num)
{
    unsigned int offset = (p->used - 1) % BN_CTX_POOL_SIZE;

    p->used -= num;
    while (num--) {
        bn_check_top(p->current->vals + offset);
        if (offset == 0) {
            offset = BN_CTX_POOL_SIZE - 1;
            p->current = p->current->prev;
        } else
            offset--;
    }
}