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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static short hpi6000_send_data_check_adr(u32 address, u32 length_in_dwords)
{
/*#define CHECKING       // comment this line in to enable checking */
#ifdef CHECKING
	if (address < (u32)MSG_ADDRESS)
		return 0;
	if (address > (u32)(QUEUE_START + QUEUE_SIZE))
		return 0;
	if ((address + (length_in_dwords << 2)) >
		(u32)(QUEUE_START + QUEUE_SIZE))
		return 0;
#else
	(void)address;
	(void)length_in_dwords;
	return 1;
#endif
}