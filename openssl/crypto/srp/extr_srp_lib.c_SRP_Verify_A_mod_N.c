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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int SRP_Verify_B_mod_N (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int SRP_Verify_A_mod_N(const BIGNUM *A, const BIGNUM *N)
{
    /* Checks if A % N == 0 */
    return SRP_Verify_B_mod_N(A, N);
}