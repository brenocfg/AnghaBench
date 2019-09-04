#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int ref_freq; } ;
struct TYPE_14__ {TYPE_6__ pll; } ;
struct TYPE_11__ {int mctlwtst; int memrdbk; int opt; int opt2; } ;
struct TYPE_12__ {TYPE_4__ reg; } ;
struct TYPE_9__ {int vcomax; } ;
struct TYPE_8__ {int vcomax; } ;
struct TYPE_10__ {TYPE_2__ system; TYPE_1__ pixel; } ;
struct matrox_fb_info {TYPE_7__ features; TYPE_5__ values; TYPE_3__ limits; } ;
struct matrox_bios {int* pins; } ;

/* Variables and functions */
 int get_unaligned_le32 (int*) ; 

__attribute__((used)) static int parse_pins3(struct matrox_fb_info *minfo,
		       const struct matrox_bios *bd)
{
	minfo->limits.pixel.vcomax	=
	minfo->limits.system.vcomax	= (bd->pins[36] == 0xFF) ? 230000			: ((bd->pins[36] + 100) * 1000);
	minfo->values.reg.mctlwtst	= get_unaligned_le32(bd->pins + 48) == 0xFFFFFFFF ?
		0x01250A21 : get_unaligned_le32(bd->pins + 48);
	/* memory config */
	minfo->values.reg.memrdbk	= ((bd->pins[57] << 21) & 0x1E000000) |
					  ((bd->pins[57] << 22) & 0x00C00000) |
					  ((bd->pins[56] <<  1) & 0x000001E0) |
					  ( bd->pins[56]        & 0x0000000F);
	minfo->values.reg.opt		= (bd->pins[54] & 7) << 10;
	minfo->values.reg.opt2		= bd->pins[58] << 12;
	minfo->features.pll.ref_freq	= (bd->pins[52] & 0x20) ? 14318 : 27000;
	return 0;
}