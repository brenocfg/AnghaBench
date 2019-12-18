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
struct TYPE_3__ {int /*<<< orphan*/  ks; } ;
struct TYPE_4__ {TYPE_1__ ks; } ;
typedef  int /*<<< orphan*/  PROV_GCM_CTX ;
typedef  TYPE_2__ PROV_ARIA_GCM_CTX ;
typedef  int /*<<< orphan*/  ARIA_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  GCM_HW_SET_KEY_CTR_FN (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aria_encrypt ; 
 int /*<<< orphan*/  aria_set_encrypt_key ; 

__attribute__((used)) static int aria_gcm_initkey(PROV_GCM_CTX *ctx, const unsigned char *key,
                            size_t keylen)
{
    PROV_ARIA_GCM_CTX *actx = (PROV_ARIA_GCM_CTX *)ctx;
    ARIA_KEY *ks = &actx->ks.ks;

    GCM_HW_SET_KEY_CTR_FN(ks, aria_set_encrypt_key, aria_encrypt, NULL);
    return 1;
}