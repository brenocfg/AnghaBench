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
struct cmac_data_st {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int CMAC_Final (int /*<<< orphan*/ ,unsigned char*,size_t*) ; 

__attribute__((used)) static int cmac_final(void *vmacctx, unsigned char *out, size_t *outl,
                      size_t outsize)
{
    struct cmac_data_st *macctx = vmacctx;

    return CMAC_Final(macctx->ctx, out, outl);
}