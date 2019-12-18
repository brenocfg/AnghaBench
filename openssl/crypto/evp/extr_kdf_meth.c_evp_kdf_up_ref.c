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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_UP_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evp_kdf_up_ref(void *vkdf)
{
    EVP_KDF *kdf = (EVP_KDF *)vkdf;
    int ref = 0;

    CRYPTO_UP_REF(&kdf->refcnt, &ref, kdf->lock);
    return 1;
}