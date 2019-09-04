#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ key_length; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; TYPE_3__ params; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int BLAKE2b_Init_key (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_F_BLAKE2B_MAC_INIT ; 
 int /*<<< orphan*/  EVP_R_NO_KEY_SET ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blake2b_mac_init(EVP_MAC_IMPL *macctx)
{
    /* Check key has been set */
    if (macctx->params.key_length == 0) {
        EVPerr(EVP_F_BLAKE2B_MAC_INIT, EVP_R_NO_KEY_SET);
        return 0;
    }

    return BLAKE2b_Init_key(&macctx->ctx, &macctx->params, macctx->key);
}