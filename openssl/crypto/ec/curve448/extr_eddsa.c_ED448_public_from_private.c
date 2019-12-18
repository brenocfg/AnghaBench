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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 scalar_t__ C448_SUCCESS ; 
 scalar_t__ c448_ed448_derive_public_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int ED448_public_from_private(OPENSSL_CTX *ctx, uint8_t out_public_key[57],
                              const uint8_t private_key[57])
{
    return c448_ed448_derive_public_key(ctx, out_public_key, private_key)
        == C448_SUCCESS;
}