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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 int /*<<< orphan*/  DH_up_ref (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_assign_DH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int EVP_PKEY_set1_DH(EVP_PKEY *pkey, DH *key)
{
    int ret = EVP_PKEY_assign_DH(pkey, key);
    if (ret)
        DH_up_ref(key);
    return ret;
}