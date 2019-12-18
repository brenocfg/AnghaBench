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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ HMAC_MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 

void HMACMD5Update(HMAC_MD5_CTX *ctx, const unsigned char *data, unsigned int data_len)
{
    MD5Update(&(ctx->ctx), data, data_len);
}