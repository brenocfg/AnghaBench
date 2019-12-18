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
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int* crc16_table ; 

__attribute__((used)) static inline __u16 crc16_byte(__u16 crc, const __u8 data)
{
    return (crc >> 8) ^ crc16_table[(crc ^ data) & 0xff];
}