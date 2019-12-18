#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cipher ) (void*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ PROV_AES_SIV_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int siv_stream_final(void *vctx, unsigned char *out, size_t *outl,
                            size_t outsize)
{
    PROV_AES_SIV_CTX *ctx = (PROV_AES_SIV_CTX *)vctx;

    if (!ctx->hw->cipher(vctx, out, NULL, 0))
        return 0;

    if (outl != NULL)
        *outl = 0;
    return 1;
}