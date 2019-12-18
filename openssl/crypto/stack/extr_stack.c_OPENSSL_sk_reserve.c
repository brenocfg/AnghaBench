#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OPENSSL_STACK ;

/* Variables and functions */
 int sk_reserve (int /*<<< orphan*/ *,int,int) ; 

int OPENSSL_sk_reserve(OPENSSL_STACK *st, int n)
{
    if (st == NULL)
        return 0;

    if (n < 0)
        return 1;
    return sk_reserve(st, n, 1);
}