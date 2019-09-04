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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ CDT ; 
 int CDT1_BS_ISOC_SHIFT ; 
 int CDT3_BA_SHIFT ; 
 int CDT3_BD_SHIFT ; 
 int /*<<< orphan*/  dim2_write_ctr (scalar_t__,int*) ; 

__attribute__((used)) static void dim2_configure_cdt(u8 ch_addr, u16 dbr_address, u16 hw_buffer_size,
			       u16 packet_length)
{
	u32 cdt[4] = { 0, 0, 0, 0 };

	if (packet_length)
		cdt[1] = ((packet_length - 1) << CDT1_BS_ISOC_SHIFT);

	cdt[3] =
		((hw_buffer_size - 1) << CDT3_BD_SHIFT) |
		(dbr_address << CDT3_BA_SHIFT);
	dim2_write_ctr(CDT + ch_addr, cdt);
}