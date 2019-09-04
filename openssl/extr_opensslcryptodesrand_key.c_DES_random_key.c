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
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 scalar_t__ DES_is_weak_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DES_set_odd_parity (int /*<<< orphan*/ *) ; 
 int RAND_priv_bytes (unsigned char*,int) ; 

int DES_random_key(DES_cblock *ret)
{
    do {
        if (RAND_priv_bytes((unsigned char *)ret, sizeof(DES_cblock)) != 1)
            return 0;
    } while (DES_is_weak_key(ret));
    DES_set_odd_parity(ret);
    return 1;
}