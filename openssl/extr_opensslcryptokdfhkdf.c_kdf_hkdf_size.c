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
struct TYPE_3__ {scalar_t__ mode; int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
 scalar_t__ EVP_KDF_HKDF_MODE_EXTRACT_ONLY ; 
 int EVP_MD_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KDF_F_KDF_HKDF_SIZE ; 
 int /*<<< orphan*/  KDF_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SIZE_MAX ; 

__attribute__((used)) static size_t kdf_hkdf_size(EVP_KDF_IMPL *impl)
{
    int sz;

    if (impl->mode != EVP_KDF_HKDF_MODE_EXTRACT_ONLY)
        return SIZE_MAX;

    if (impl->md == NULL) {
        KDFerr(KDF_F_KDF_HKDF_SIZE, KDF_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    sz = EVP_MD_size(impl->md);
    if (sz < 0)
        return 0;

    return sz;
}