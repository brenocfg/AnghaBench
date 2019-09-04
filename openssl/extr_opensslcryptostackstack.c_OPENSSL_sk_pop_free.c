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
struct TYPE_4__ {int num; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  (* OPENSSL_sk_freefunc ) (char*) ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_sk_free (TYPE_1__*) ; 

void OPENSSL_sk_pop_free(OPENSSL_STACK *st, OPENSSL_sk_freefunc func)
{
    int i;

    if (st == NULL)
        return;
    for (i = 0; i < st->num; i++)
        if (st->data[i] != NULL)
            func((char *)st->data[i]);
    OPENSSL_sk_free(st);
}