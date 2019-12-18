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
typedef  int /*<<< orphan*/  RSA_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  const rsa_pkcs1_ossl_meth ; 

const RSA_METHOD *RSA_PKCS1_OpenSSL(void)
{
    return &rsa_pkcs1_ossl_meth;
}