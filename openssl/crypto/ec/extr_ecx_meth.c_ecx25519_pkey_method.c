#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* pcc; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_METHOD ;

/* Variables and functions */
 TYPE_1__ OPENSSL_s390xcap_P ; 
 int S390X_CAPBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S390X_SCALAR_MULTIPLY_X25519 ; 
 int /*<<< orphan*/  const ecx25519_pkey_meth ; 
 int /*<<< orphan*/  const ecx25519_s390x_pkey_meth ; 

const EVP_PKEY_METHOD *ecx25519_pkey_method(void)
{
#ifdef S390X_EC_ASM
    if (OPENSSL_s390xcap_P.pcc[1] & S390X_CAPBIT(S390X_SCALAR_MULTIPLY_X25519))
        return &ecx25519_s390x_pkey_meth;
#endif
    return &ecx25519_pkey_meth;
}