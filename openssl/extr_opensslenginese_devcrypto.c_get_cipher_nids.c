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
 int* known_cipher_nids ; 
 int known_cipher_nids_amount ; 

__attribute__((used)) static int get_cipher_nids(const int **nids)
{
    *nids = known_cipher_nids;
    return known_cipher_nids_amount;
}