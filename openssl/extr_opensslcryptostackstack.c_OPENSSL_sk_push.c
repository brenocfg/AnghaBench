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
struct TYPE_4__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int OPENSSL_sk_insert (TYPE_1__*,void const*,int /*<<< orphan*/ ) ; 

int OPENSSL_sk_push(OPENSSL_STACK *st, const void *data)
{
    if (st == NULL)
        return -1;
    return OPENSSL_sk_insert(st, data, st->num);
}