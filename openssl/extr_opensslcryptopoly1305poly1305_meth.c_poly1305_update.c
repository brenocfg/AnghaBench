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
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  POLY1305 ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  Poly1305_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static int poly1305_update(EVP_MAC_IMPL *ctx, const unsigned char *data,
                       size_t datalen)
{
    POLY1305 *poly_ctx = ctx->ctx;

    /* poly1305 has nothing to return in its update function */
    Poly1305_Update(poly_ctx, data, datalen);
    return 1;
}