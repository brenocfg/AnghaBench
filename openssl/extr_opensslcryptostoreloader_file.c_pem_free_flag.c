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
 int /*<<< orphan*/  OPENSSL_free (void*) ; 
 int /*<<< orphan*/  OPENSSL_secure_clear_free (void*,size_t) ; 

__attribute__((used)) static void pem_free_flag(void *pem_data, int secure, size_t num)
{
    if (secure)
        OPENSSL_secure_clear_free(pem_data, num);
    else
        OPENSSL_free(pem_data);
}