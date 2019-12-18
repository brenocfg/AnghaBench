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
struct TYPE_3__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_load_strings_const (TYPE_1__*) ; 
 int /*<<< orphan*/ * ERR_reason_error_string (int /*<<< orphan*/ ) ; 
 TYPE_1__* OSSL_STORE_str_reasons ; 

int ERR_load_OSSL_STORE_strings(void)
{
#ifndef OPENSSL_NO_ERR
    if (ERR_reason_error_string(OSSL_STORE_str_reasons[0].error) == NULL)
        ERR_load_strings_const(OSSL_STORE_str_reasons);
#endif
    return 1;
}