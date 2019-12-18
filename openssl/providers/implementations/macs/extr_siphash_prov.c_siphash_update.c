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
struct siphash_data_st {int /*<<< orphan*/  siphash; } ;

/* Variables and functions */
 int /*<<< orphan*/  SipHash_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static int siphash_update(void *vmacctx, const unsigned char *data,
                       size_t datalen)
{
    struct siphash_data_st *ctx = vmacctx;

    SipHash_Update(&ctx->siphash, data, datalen);
    return 1;
}