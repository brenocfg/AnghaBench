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
struct blake2_mac_data_st {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int BLAKE2_UPDATE (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static int blake2_mac_update(void *vmacctx,
                             const unsigned char *data, size_t datalen)
{
    struct blake2_mac_data_st *macctx = vmacctx;

    return BLAKE2_UPDATE(&macctx->ctx, data, datalen);
}