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
 int /*<<< orphan*/  avc_bridgeco_fill_extension_addr (int*,int*) ; 

__attribute__((used)) static inline void
avc_bridgeco_fill_plug_info_extension_command(u8 *buf, u8 *addr,
					      unsigned int itype)
{
	buf[0] = 0x01;	/* AV/C STATUS */
	buf[2] = 0x02;	/* AV/C GENERAL PLUG INFO */
	buf[3] = 0xc0;	/* BridgeCo extension */
	avc_bridgeco_fill_extension_addr(buf, addr);
	buf[9] = itype;	/* info type */
}