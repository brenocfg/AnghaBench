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
typedef  int ushort ;
typedef  int uchar ;
typedef  scalar_t__ PortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  AscSetChipLramAddr (scalar_t__,int) ; 
 scalar_t__ IOP_RAM_DATA ; 
 int inpw (scalar_t__) ; 

__attribute__((used)) static void
AscMemWordCopyPtrFromLram(PortAddr iop_base,
			  ushort s_addr, uchar *d_buffer, int words)
{
	int i;
	ushort word;

	AscSetChipLramAddr(iop_base, s_addr);
	for (i = 0; i < 2 * words; i += 2) {
		word = inpw(iop_base + IOP_RAM_DATA);
		d_buffer[i] = word & 0xff;
		d_buffer[i + 1] = (word >> 8) & 0xff;
	}
}