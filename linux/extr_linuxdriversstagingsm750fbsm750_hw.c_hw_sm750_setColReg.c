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
typedef  int ushort ;
struct lynxfb_crtc {size_t channel; } ;

/* Variables and functions */
#define  CRT_PALETTE_RAM 129 
#define  PANEL_PALETTE_RAM 128 
 int /*<<< orphan*/  poke32 (unsigned int,int) ; 

int hw_sm750_setColReg(struct lynxfb_crtc *crtc, ushort index,
		       ushort red, ushort green, ushort blue)
{
	static unsigned int add[] = {PANEL_PALETTE_RAM, CRT_PALETTE_RAM};

	poke32(add[crtc->channel] + index * 4,
	       (red << 16) | (green << 8) | blue);
	return 0;
}