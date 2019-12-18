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
typedef  TYPE_1__ KDF_SCRYPT ;

/* Variables and functions */

__attribute__((used)) static void kdf_scrypt_init(KDF_SCRYPT *ctx)
{
    /* Default values are the most conservative recommendation given in the
     * original paper of C. Percival. Derivation uses roughly 1 GiB of memory
     * for this parameter choice (approx. 128 * r * N * p bytes).
     */
    ctx->N = 1 << 20;
    ctx->r = 8;
    ctx->p = 1;
    ctx->maxmem_bytes = 1025 * 1024 * 1024;
}