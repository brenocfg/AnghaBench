#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num; scalar_t__ sorted; void const** data; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int max_nodes ; 
 int /*<<< orphan*/  memmove (void const**,void const**,int) ; 
 int /*<<< orphan*/  sk_reserve (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int OPENSSL_sk_insert(OPENSSL_STACK *st, const void *data, int loc)
{
    if (st == NULL || st->num == max_nodes)
        return 0;

    if (!sk_reserve(st, 1, 0))
        return 0;

    if ((loc >= st->num) || (loc < 0)) {
        st->data[st->num] = data;
    } else {
        memmove(&st->data[loc + 1], &st->data[loc],
                sizeof(st->data[0]) * (st->num - loc));
        st->data[loc] = data;
    }
    st->num++;
    st->sorted = 0;
    return st->num;
}