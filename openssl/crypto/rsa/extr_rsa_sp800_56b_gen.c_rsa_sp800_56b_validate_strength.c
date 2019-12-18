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
 int RSA_FIPS1864_MAX_KEYGEN_STRENGTH ; 
 int RSA_FIPS1864_MIN_KEYGEN_STRENGTH ; 
 int /*<<< orphan*/  RSA_F_RSA_SP800_56B_VALIDATE_STRENGTH ; 
 int /*<<< orphan*/  RSA_R_INVALID_MODULUS ; 
 int /*<<< orphan*/  RSA_R_INVALID_STRENGTH ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rsa_compute_security_bits (int) ; 

int rsa_sp800_56b_validate_strength(int nbits, int strength)
{
    int s = (int)rsa_compute_security_bits(nbits);

    if (s < RSA_FIPS1864_MIN_KEYGEN_STRENGTH
            || s > RSA_FIPS1864_MAX_KEYGEN_STRENGTH) {
        RSAerr(RSA_F_RSA_SP800_56B_VALIDATE_STRENGTH, RSA_R_INVALID_MODULUS);
        return 0;
    }
    if (strength != -1 && s != strength) {
        RSAerr(RSA_F_RSA_SP800_56B_VALIDATE_STRENGTH, RSA_R_INVALID_STRENGTH);
        return 0;
    }
    return 1;
}