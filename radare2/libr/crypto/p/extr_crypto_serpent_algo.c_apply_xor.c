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
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int DW_BY_BLOCK ; 

void apply_xor(ut32 block[DW_BY_BLOCK], ut32 subkey[DW_BY_BLOCK]) {
	int i;
	for (i = 0; i < DW_BY_BLOCK; i++) {
		block[i] ^= subkey[i];
	}
}