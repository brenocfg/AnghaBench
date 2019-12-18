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
typedef  size_t u8 ;

/* Variables and functions */
 int RFCOMM_UIH ; 
 size_t __crc (size_t*) ; 
 int* rfcomm_crc_table ; 

__attribute__((used)) static inline int __check_fcs(u8 *data, int type, u8 fcs)
{
	u8 f = __crc(data);

	if (type != RFCOMM_UIH)
		f = rfcomm_crc_table[f ^ data[2]];

	return rfcomm_crc_table[f ^ fcs] != 0xcf;
}