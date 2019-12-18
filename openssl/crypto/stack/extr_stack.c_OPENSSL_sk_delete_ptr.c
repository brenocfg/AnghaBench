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
struct TYPE_4__ {int num; void const** data; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 void* internal_delete (TYPE_1__*,int) ; 

void *OPENSSL_sk_delete_ptr(OPENSSL_STACK *st, const void *p)
{
    int i;

    for (i = 0; i < st->num; i++)
        if (st->data[i] == p)
            return internal_delete(st, i);
    return NULL;
}