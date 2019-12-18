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
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  EVP_CTRL_GET_RC2_KEY_BITS ; 
 int RC2_128_MAGIC ; 
 int RC2_40_MAGIC ; 
 int RC2_64_MAGIC ; 

__attribute__((used)) static int rc2_meth_to_magic(EVP_CIPHER_CTX *e)
{
    int i;

    if (EVP_CIPHER_CTX_ctrl(e, EVP_CTRL_GET_RC2_KEY_BITS, 0, &i) <= 0)
        return 0;
    if (i == 128)
        return RC2_128_MAGIC;
    else if (i == 64)
        return RC2_64_MAGIC;
    else if (i == 40)
        return RC2_40_MAGIC;
    else
        return 0;
}