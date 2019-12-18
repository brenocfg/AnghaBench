#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OCB128_CONTEXT ;

/* Variables and functions */
 int ocb_finish (int /*<<< orphan*/ *,unsigned char*,size_t,int) ; 

int CRYPTO_ocb128_tag(OCB128_CONTEXT *ctx, unsigned char *tag, size_t len)
{
    return ocb_finish(ctx, tag, len, 1);
}