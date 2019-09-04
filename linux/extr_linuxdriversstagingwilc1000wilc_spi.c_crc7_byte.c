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

/* Variables and functions */
 int* crc7_syndrome_table ; 

__attribute__((used)) static u8 crc7_byte(u8 crc, u8 data)
{
	return crc7_syndrome_table[(crc << 1) ^ data];
}