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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int ead_tx_iv ; 
 int ivofs_idx ; 
 int ivofs_vec ; 

__attribute__((used)) static uint32_t
ead_get_tx_iv(void)
{
	unsigned int ofs;

	ofs = 1 + ((ivofs_vec >> 2 * ivofs_idx) & 0x3);
	ivofs_idx = (ivofs_idx + 1) % 16;
	ead_tx_iv += ofs;

	return ead_tx_iv;
}