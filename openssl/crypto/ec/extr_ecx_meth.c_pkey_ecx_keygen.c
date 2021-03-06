#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pmeth; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_OP_KEYGEN ; 
 int ecx_key_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_ecx_keygen(EVP_PKEY_CTX *ctx, EVP_PKEY *pkey)
{
    return ecx_key_op(pkey, ctx->pmeth->pkey_id, NULL, NULL, 0, KEY_OP_KEYGEN);
}