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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline void dlci_to_q922(u8 *hdr, u16 dlci)
{
	hdr[0] = (dlci >> 2) & 0xFC;
	hdr[1] = ((dlci << 4) & 0xF0) | 0x01;
}