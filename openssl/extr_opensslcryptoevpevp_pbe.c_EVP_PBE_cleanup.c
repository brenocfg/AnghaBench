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
 int /*<<< orphan*/  free_evp_pbe_ctl ; 
 int /*<<< orphan*/ * pbe_algs ; 
 int /*<<< orphan*/  sk_EVP_PBE_CTL_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void EVP_PBE_cleanup(void)
{
    sk_EVP_PBE_CTL_pop_free(pbe_algs, free_evp_pbe_ctl);
    pbe_algs = NULL;
}