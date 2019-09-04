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
struct pem_password_cb_data {int dummy; } ;
typedef  int /*<<< orphan*/  CRYPTO_EX_DATA ;

/* Variables and functions */
 void* OPENSSL_memdup (void*,int) ; 

__attribute__((used)) static int ui_dup_method_data(CRYPTO_EX_DATA *to, const CRYPTO_EX_DATA *from,
                              void *from_d, int idx, long argl, void *argp)
{
    void **pptr = (void **)from_d;
    if (*pptr != NULL)
        *pptr = OPENSSL_memdup(*pptr, sizeof(struct pem_password_cb_data));
    return 1;
}