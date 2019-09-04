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
struct TYPE_3__ {int num; scalar_t__* data; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */

void *OPENSSL_sk_value(const OPENSSL_STACK *st, int i)
{
    if (st == NULL || i < 0 || i >= st->num)
        return NULL;
    return (void *)st->data[i];
}