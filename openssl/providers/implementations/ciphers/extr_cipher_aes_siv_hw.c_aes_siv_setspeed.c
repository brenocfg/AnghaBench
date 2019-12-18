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
struct TYPE_2__ {int /*<<< orphan*/  siv; } ;
typedef  int /*<<< orphan*/  SIV128_CONTEXT ;
typedef  TYPE_1__ PROV_AES_SIV_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_siv128_speed (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void aes_siv_setspeed(void *vctx, int speed)
{
    PROV_AES_SIV_CTX *ctx = (PROV_AES_SIV_CTX *)vctx;
    SIV128_CONTEXT *sctx = &ctx->siv;

    CRYPTO_siv128_speed(sctx, (int)speed);
}