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
 int /*<<< orphan*/  CRYPTO_F_FIPS_MODE_SET ; 
 int /*<<< orphan*/  CRYPTO_R_FIPS_MODE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int FIPS_mode_set(int r)
{
    if (r == 0)
        return 1;
    CRYPTOerr(CRYPTO_F_FIPS_MODE_SET, CRYPTO_R_FIPS_MODE_NOT_SUPPORTED);
    return 0;
}