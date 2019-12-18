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
 int /*<<< orphan*/  OSSL_BSEARCH_FIRST_VALUE_ON_MATCH ; 
 int internal_find (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 

int OPENSSL_sk_find(OPENSSL_STACK *st, const void *data)
{
    return internal_find(st, data, OSSL_BSEARCH_FIRST_VALUE_ON_MATCH);
}