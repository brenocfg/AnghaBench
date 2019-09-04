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
struct TYPE_4__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ERR_func_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_load_strings_const (TYPE_1__*) ; 
 TYPE_1__* EVP_str_functs ; 
 TYPE_1__* EVP_str_reasons ; 

int ERR_load_EVP_strings(void)
{
#ifndef OPENSSL_NO_ERR
    if (ERR_func_error_string(EVP_str_functs[0].error) == NULL) {
        ERR_load_strings_const(EVP_str_functs);
        ERR_load_strings_const(EVP_str_reasons);
    }
#endif
    return 1;
}