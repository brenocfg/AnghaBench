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
typedef  int /*<<< orphan*/  PROV_CCM_CTX ;

/* Variables and functions */
 int ccm_cipher_internal (int /*<<< orphan*/ *,unsigned char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ccm_stream_final(void *vctx, unsigned char *out, size_t *outl,
                            size_t outsize)
{
    PROV_CCM_CTX *ctx = (PROV_CCM_CTX *)vctx;
    int i;

    i = ccm_cipher_internal(ctx, out, outl, NULL, 0);
    if (i <= 0)
        return 0;

    *outl = 0;
    return 1;
}