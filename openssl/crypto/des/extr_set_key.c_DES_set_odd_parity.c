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
typedef  size_t* DES_cblock ;

/* Variables and functions */
 unsigned int DES_KEY_SZ ; 
 size_t* odd_parity ; 

void DES_set_odd_parity(DES_cblock *key)
{
    unsigned int i;

    for (i = 0; i < DES_KEY_SZ; i++)
        (*key)[i] = odd_parity[(*key)[i]];
}