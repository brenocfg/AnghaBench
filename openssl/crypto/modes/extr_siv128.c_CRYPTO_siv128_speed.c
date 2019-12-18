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
struct TYPE_3__ {int crypto_ok; } ;
typedef  TYPE_1__ SIV128_CONTEXT ;

/* Variables and functions */

int CRYPTO_siv128_speed(SIV128_CONTEXT *ctx, int arg)
{
    ctx->crypto_ok = (arg == 1) ? -1 : 1;
    return 1;
}