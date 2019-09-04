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
struct TYPE_3__ {int N; int r; int p; int maxmem_bytes; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */

__attribute__((used)) static void kdf_scrypt_init(EVP_KDF_IMPL *impl)
{
    /* Default values are the most conservative recommendation given in the
     * original paper of C. Percival. Derivation uses roughly 1 GiB of memory
     * for this parameter choice (approx. 128 * r * N * p bytes).
     */
    impl->N = 1 << 20;
    impl->r = 8;
    impl->p = 1;
    impl->maxmem_bytes = 1025 * 1024 * 1024;
}