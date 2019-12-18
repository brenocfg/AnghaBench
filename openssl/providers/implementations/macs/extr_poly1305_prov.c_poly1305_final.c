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
struct poly1305_data_st {int /*<<< orphan*/  poly1305; } ;

/* Variables and functions */
 int /*<<< orphan*/  Poly1305_Final (int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int poly1305_final(void *vmacctx, unsigned char *out, size_t *outl,
                          size_t outsize)
{
    struct poly1305_data_st *ctx = vmacctx;

    Poly1305_Final(&ctx->poly1305, out);
    return 1;
}