#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * counter; } ;
struct TYPE_4__ {scalar_t__ oiv; scalar_t__ iv_set; } ;
typedef  TYPE_1__ PROV_CIPHER_CTX ;
typedef  TYPE_2__ PROV_CHACHA20_CTX ;

/* Variables and functions */
 unsigned int CHACHA_CTR_SIZE ; 
 int /*<<< orphan*/  CHACHA_U8TOU32 (scalar_t__) ; 

__attribute__((used)) static int chacha20_initiv(PROV_CIPHER_CTX *bctx)
{
    PROV_CHACHA20_CTX *ctx = (PROV_CHACHA20_CTX *)bctx;
    unsigned int i;

    if (bctx->iv_set) {
        for (i = 0; i < CHACHA_CTR_SIZE; i += 4)
            ctx->counter[i / 4] = CHACHA_U8TOU32(bctx->oiv + i);
    }
    return 1;
}