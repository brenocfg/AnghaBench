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
 int /*<<< orphan*/  Poly1305_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static int poly1305_update(void *vmacctx, const unsigned char *data,
                       size_t datalen)
{
    struct poly1305_data_st *ctx = vmacctx;

    /* poly1305 has nothing to return in its update function */
    Poly1305_Update(&ctx->poly1305, data, datalen);
    return 1;
}