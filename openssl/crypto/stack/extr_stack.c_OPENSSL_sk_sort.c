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
struct TYPE_3__ {int sorted; int num; int /*<<< orphan*/ * comp; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

void OPENSSL_sk_sort(OPENSSL_STACK *st)
{
    if (st != NULL && !st->sorted && st->comp != NULL) {
        if (st->num > 1)
            qsort(st->data, st->num, sizeof(void *), st->comp);
        st->sorted = 1; /* empty or single-element stack is considered sorted */
    }
}