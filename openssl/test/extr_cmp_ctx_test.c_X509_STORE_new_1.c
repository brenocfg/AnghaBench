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
typedef  int /*<<< orphan*/  X509_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  X509_STORE_get0_param (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_set_flags (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static X509_STORE *X509_STORE_new_1(void) {
    X509_STORE *store = X509_STORE_new();

    if (store != NULL)
        X509_VERIFY_PARAM_set_flags(X509_STORE_get0_param(store), 1);
    return store;
}