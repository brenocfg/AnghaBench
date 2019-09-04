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
struct TYPE_4__ {int /*<<< orphan*/  seedlen; int /*<<< orphan*/  seed; int /*<<< orphan*/  seclen; int /*<<< orphan*/  sec; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kdf_tls1_prf_reset(EVP_KDF_IMPL *impl)
{
    OPENSSL_clear_free(impl->sec, impl->seclen);
    OPENSSL_cleanse(impl->seed, impl->seedlen);
    memset(impl, 0, sizeof(*impl));
}