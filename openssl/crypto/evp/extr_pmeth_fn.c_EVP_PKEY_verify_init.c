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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_OP_VERIFY ; 
 int evp_pkey_signature_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int EVP_PKEY_verify_init(EVP_PKEY_CTX *ctx)
{
    return evp_pkey_signature_init(ctx, EVP_PKEY_OP_VERIFY);
}