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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxkad_ci ; 

__attribute__((used)) static int rxkad_init(void)
{
	/* pin the cipher we need so that the crypto layer doesn't invoke
	 * keventd to go get it */
	rxkad_ci = crypto_alloc_skcipher("pcbc(fcrypt)", 0, CRYPTO_ALG_ASYNC);
	return PTR_ERR_OR_ZERO(rxkad_ci);
}