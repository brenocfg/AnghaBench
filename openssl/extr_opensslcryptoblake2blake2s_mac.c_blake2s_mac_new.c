#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  params; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  blake2s_param_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static EVP_MAC_IMPL *blake2s_mac_new(void)
{
    EVP_MAC_IMPL *macctx = OPENSSL_zalloc(sizeof(*macctx));
    if (macctx != NULL) {
        blake2s_param_init(&macctx->params);
        /* ctx initialization is deferred to BLAKE2s_Init() */
    }
    return macctx;
}