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
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int BLAKE2b_Update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static int blake2b_mac_update(EVP_MAC_IMPL *macctx, const unsigned char *data,
                              size_t datalen)
{
    return BLAKE2b_Update(&macctx->ctx, data, datalen);
}