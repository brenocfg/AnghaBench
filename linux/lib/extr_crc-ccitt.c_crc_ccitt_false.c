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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  crc_ccitt_false_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 crc_ccitt_false(u16 crc, u8 const *buffer, size_t len)
{
	while (len--)
		crc = crc_ccitt_false_byte(crc, *buffer++);
	return crc;
}