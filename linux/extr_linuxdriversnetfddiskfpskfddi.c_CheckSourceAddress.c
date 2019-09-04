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
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CheckSourceAddress(unsigned char *frame, unsigned char *hw_addr)
{
	unsigned char SRBit;

	if ((((unsigned long) frame[1 + 6]) & ~0x01) != 0) // source routing bit

		return;
	if ((unsigned short) frame[1 + 10] != 0)
		return;
	SRBit = frame[1 + 6] & 0x01;
	memcpy(&frame[1 + 6], hw_addr, ETH_ALEN);
	frame[8] |= SRBit;
}