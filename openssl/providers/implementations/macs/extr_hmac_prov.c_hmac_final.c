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
struct hmac_data_st {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ ,unsigned char*,unsigned int*) ; 

__attribute__((used)) static int hmac_final(void *vmacctx, unsigned char *out, size_t *outl,
                      size_t outsize)
{
    unsigned int hlen;
    struct hmac_data_st *macctx = vmacctx;

    if (!HMAC_Final(macctx->ctx, out, &hlen))
        return 0;
    if (outl != NULL)
        *outl = hlen;
    return 1;
}