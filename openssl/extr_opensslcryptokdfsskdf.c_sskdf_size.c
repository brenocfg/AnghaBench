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
struct TYPE_3__ {int /*<<< orphan*/ * md; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
 int EVP_MD_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KDF_F_SSKDF_SIZE ; 
 int /*<<< orphan*/  KDF_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t sskdf_size(EVP_KDF_IMPL *impl)
{
    int len;

    if (impl->md == NULL) {
        KDFerr(KDF_F_SSKDF_SIZE, KDF_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    len = EVP_MD_size(impl->md);
    return (len <= 0) ? 0 : (size_t)len;
}