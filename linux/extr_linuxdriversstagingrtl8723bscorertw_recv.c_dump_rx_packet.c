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

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 

__attribute__((used)) static inline void dump_rx_packet(u8 *ptr)
{
	int i;

	DBG_871X("#############################\n");
	for (i = 0; i < 64; i = i+8)
		DBG_871X("%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:\n", *(ptr+i),
		*(ptr+i+1), *(ptr+i+2), *(ptr+i+3), *(ptr+i+4), *(ptr+i+5), *(ptr+i+6), *(ptr+i+7));
	DBG_871X("#############################\n");
}