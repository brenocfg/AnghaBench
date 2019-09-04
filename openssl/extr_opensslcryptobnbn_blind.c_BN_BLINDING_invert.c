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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BN_BLINDING ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_BLINDING_invert_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int BN_BLINDING_invert(BIGNUM *n, BN_BLINDING *b, BN_CTX *ctx)
{
    return BN_BLINDING_invert_ex(n, NULL, b, ctx);
}