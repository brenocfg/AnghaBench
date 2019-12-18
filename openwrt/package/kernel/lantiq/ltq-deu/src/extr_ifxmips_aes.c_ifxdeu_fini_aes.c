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
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifxdeu_aes_alg ; 
 int /*<<< orphan*/  ifxdeu_cbc_aes_alg ; 
 int /*<<< orphan*/  ifxdeu_ctr_basic_aes_alg ; 
 int /*<<< orphan*/  ifxdeu_ctr_rfc3686_aes_alg ; 
 int /*<<< orphan*/  ifxdeu_ecb_aes_alg ; 

void ifxdeu_fini_aes (void)
{
    crypto_unregister_alg (&ifxdeu_aes_alg);
    crypto_unregister_alg (&ifxdeu_ecb_aes_alg);
    crypto_unregister_alg (&ifxdeu_cbc_aes_alg);
    crypto_unregister_alg (&ifxdeu_ctr_basic_aes_alg);
    crypto_unregister_alg (&ifxdeu_ctr_rfc3686_aes_alg);

}