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
typedef  int ut32 ;

/* Variables and functions */
 int DW_BY_BLOCK ; 
 int* IPTable ; 
 scalar_t__ get_bit (int,int) ; 

void apply_IP(ut32 in[DW_BY_BLOCK], ut32 out[DW_BY_BLOCK]) {
	int index;
	int i;
	for (i = 0; i < DW_BY_BLOCK*32; i++) {
		index = IPTable[i];
		out[i/32] ^= (-(ut32)get_bit (index%32, in[index/32]) ^ out[i/32])
			& (1 << i);
	}
}