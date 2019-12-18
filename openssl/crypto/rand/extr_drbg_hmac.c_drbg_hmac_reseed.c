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
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int drbg_hmac_update (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drbg_hmac_reseed(RAND_DRBG *drbg,
                            const unsigned char *ent, size_t ent_len,
                            const unsigned char *adin, size_t adin_len)
{
    /* (Step 2) (K,V) = HMAC_DRBG_Update(entropy||additional_input, K, V) */
    return drbg_hmac_update(drbg, ent, ent_len, adin, adin_len, NULL, 0);
}