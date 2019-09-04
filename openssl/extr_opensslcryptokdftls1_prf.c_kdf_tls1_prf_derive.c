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
struct TYPE_3__ {scalar_t__ seedlen; int /*<<< orphan*/  seed; int /*<<< orphan*/  seclen; int /*<<< orphan*/ * sec; int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  KDF_F_KDF_TLS1_PRF_DERIVE ; 
 int /*<<< orphan*/  KDF_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  KDF_R_MISSING_SECRET ; 
 int /*<<< orphan*/  KDF_R_MISSING_SEED ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tls1_prf_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned char*,size_t) ; 

__attribute__((used)) static int kdf_tls1_prf_derive(EVP_KDF_IMPL *impl, unsigned char *key,
                               size_t keylen)
{
    if (impl->md == NULL) {
        KDFerr(KDF_F_KDF_TLS1_PRF_DERIVE, KDF_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    if (impl->sec == NULL) {
        KDFerr(KDF_F_KDF_TLS1_PRF_DERIVE, KDF_R_MISSING_SECRET);
        return 0;
    }
    if (impl->seedlen == 0) {
        KDFerr(KDF_F_KDF_TLS1_PRF_DERIVE, KDF_R_MISSING_SEED);
        return 0;
    }
    return tls1_prf_alg(impl->md, impl->sec, impl->seclen,
                        impl->seed, impl->seedlen,
                        key, keylen);
}