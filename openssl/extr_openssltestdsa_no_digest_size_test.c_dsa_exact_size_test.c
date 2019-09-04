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
 scalar_t__ sign_and_verify (int) ; 

__attribute__((used)) static int dsa_exact_size_test(void) {
    /*
     * For a 2048-bit p, q should be either 224 or 256 bits per the table in
     * FIPS 186-4 4.2.
     */

    return sign_and_verify(224 / 8) && sign_and_verify(256 / 8);
}