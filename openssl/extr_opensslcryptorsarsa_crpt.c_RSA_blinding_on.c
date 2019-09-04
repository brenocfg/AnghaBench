#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * blinding; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  RSA_FLAG_BLINDING ; 
 int /*<<< orphan*/  RSA_FLAG_NO_BLINDING ; 
 int /*<<< orphan*/  RSA_blinding_off (TYPE_1__*) ; 
 int /*<<< orphan*/ * RSA_setup_blinding (TYPE_1__*,int /*<<< orphan*/ *) ; 

int RSA_blinding_on(RSA *rsa, BN_CTX *ctx)
{
    int ret = 0;

    if (rsa->blinding != NULL)
        RSA_blinding_off(rsa);

    rsa->blinding = RSA_setup_blinding(rsa, ctx);
    if (rsa->blinding == NULL)
        goto err;

    rsa->flags |= RSA_FLAG_BLINDING;
    rsa->flags &= ~RSA_FLAG_NO_BLINDING;
    ret = 1;
 err:
    return ret;
}