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
 int /*<<< orphan*/  OPENSSL_ia32_rdseed_bytes ; 
 int sanity_check_bytes (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int sanity_check_rdseed_bytes(void)
{
    /*-
     * RDSEED may take many retries to succeed; note that this is effectively
     * multiplied by the 8x retry loop in asm, and failure probabilities are
     * increased by the fact that we need either 4 or 8 samples depending on
     * the platform.
     */
    return sanity_check_bytes(OPENSSL_ia32_rdseed_bytes, 1000, 1, 10000, 10);
}