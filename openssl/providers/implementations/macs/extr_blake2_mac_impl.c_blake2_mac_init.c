#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ key_length; } ;
struct blake2_mac_data_st {int /*<<< orphan*/  key; TYPE_1__ params; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int BLAKE2_INIT_KEY (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_NO_KEY_SET ; 

__attribute__((used)) static int blake2_mac_init(void *vmacctx)
{
    struct blake2_mac_data_st *macctx = vmacctx;

    /* Check key has been set */
    if (macctx->params.key_length == 0) {
        ERR_raise(ERR_LIB_PROV, PROV_R_NO_KEY_SET);
        return 0;
    }

    return BLAKE2_INIT_KEY(&macctx->ctx, &macctx->params, macctx->key);
}