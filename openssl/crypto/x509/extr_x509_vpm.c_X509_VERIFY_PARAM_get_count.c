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

/* Variables and functions */
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_table ; 
 scalar_t__ param_table ; 
 scalar_t__ sk_X509_VERIFY_PARAM_num (scalar_t__) ; 

int X509_VERIFY_PARAM_get_count(void)
{
    int num = OSSL_NELEM(default_table);
    if (param_table)
        num += sk_X509_VERIFY_PARAM_num(param_table);
    return num;
}