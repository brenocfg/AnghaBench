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
struct TYPE_3__ {scalar_t__ shift; int /*<<< orphan*/  num_bits; int /*<<< orphan*/  Nr; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ BN_RECP_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 

int BN_RECP_CTX_set(BN_RECP_CTX *recp, const BIGNUM *d, BN_CTX *ctx)
{
    if (!BN_copy(&(recp->N), d))
        return 0;
    BN_zero(&(recp->Nr));
    recp->num_bits = BN_num_bits(d);
    recp->shift = 0;
    return 1;
}