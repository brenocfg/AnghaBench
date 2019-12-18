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
struct TYPE_3__ {int /*<<< orphan*/  md_ctx; int /*<<< orphan*/  md; } ;
typedef  TYPE_1__ HMAC_CTX ;

/* Variables and functions */
 int EVP_DigestUpdate (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int HMAC_Update(HMAC_CTX *ctx, const unsigned char *data, size_t len)
{
    if (!ctx->md)
        return 0;
    return EVP_DigestUpdate(ctx->md_ctx, data, len);
}