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
 int /*<<< orphan*/  EVP_F_RC2_MAGIC_TO_METH ; 
 int /*<<< orphan*/  EVP_R_UNSUPPORTED_KEY_SIZE ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RC2_128_MAGIC ; 
 int RC2_40_MAGIC ; 
 int RC2_64_MAGIC ; 

__attribute__((used)) static int rc2_magic_to_meth(int i)
{
    if (i == RC2_128_MAGIC)
        return 128;
    else if (i == RC2_64_MAGIC)
        return 64;
    else if (i == RC2_40_MAGIC)
        return 40;
    else {
        EVPerr(EVP_F_RC2_MAGIC_TO_METH, EVP_R_UNSUPPORTED_KEY_SIZE);
        return 0;
    }
}