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
struct TYPE_2__ {int* pcc; int* kdsa; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_METHOD ;

/* Variables and functions */
 TYPE_1__ OPENSSL_s390xcap_P ; 
 int S390X_CAPBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S390X_EDDSA_SIGN_ED448 ; 
 int /*<<< orphan*/  S390X_EDDSA_VERIFY_ED448 ; 
 int /*<<< orphan*/  S390X_SCALAR_MULTIPLY_ED448 ; 
 int /*<<< orphan*/  const ed448_pkey_meth ; 
 int /*<<< orphan*/  const ed448_s390x_pkey_meth ; 

const EVP_PKEY_METHOD *ed448_pkey_method(void)
{
#ifdef S390X_EC_ASM
    if (OPENSSL_s390xcap_P.pcc[1] & S390X_CAPBIT(S390X_SCALAR_MULTIPLY_ED448)
        && OPENSSL_s390xcap_P.kdsa[0] & S390X_CAPBIT(S390X_EDDSA_SIGN_ED448)
        && OPENSSL_s390xcap_P.kdsa[0] & S390X_CAPBIT(S390X_EDDSA_VERIFY_ED448))
        return &ed448_s390x_pkey_meth;
#endif
    return &ed448_pkey_meth;
}