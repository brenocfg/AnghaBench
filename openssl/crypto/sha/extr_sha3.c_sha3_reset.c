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
struct TYPE_3__ {scalar_t__ bufsz; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ KECCAK1600_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void sha3_reset(KECCAK1600_CTX *ctx)
{
    memset(ctx->A, 0, sizeof(ctx->A));
    ctx->bufsz = 0;
}