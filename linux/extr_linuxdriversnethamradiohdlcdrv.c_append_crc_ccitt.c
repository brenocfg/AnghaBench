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
 int crc_ccitt (int,unsigned char*,int) ; 

__attribute__((used)) static inline void append_crc_ccitt(unsigned char *buffer, int len)
{
 	unsigned int crc = crc_ccitt(0xffff, buffer, len) ^ 0xffff;
	buffer += len;
	*buffer++ = crc;
	*buffer++ = crc >> 8;
}