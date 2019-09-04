#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct fb_info {int dummy; } ;
struct TYPE_8__ {int addr; int data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* chips_init_ar ; 
 TYPE_1__* chips_init_cr ; 
 TYPE_1__* chips_init_fr ; 
 TYPE_1__* chips_init_gr ; 
 TYPE_1__* chips_init_sr ; 
 TYPE_1__* chips_init_xr ; 
 scalar_t__ mmio_base ; 
 int /*<<< orphan*/  write_ar (int,int) ; 
 int /*<<< orphan*/  write_cr (int,int) ; 
 int /*<<< orphan*/  write_fr (int,int) ; 
 int /*<<< orphan*/  write_gr (int,int) ; 
 int /*<<< orphan*/  write_sr (int,int) ; 
 int /*<<< orphan*/  write_xr (int,int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void chips_hw_init(struct fb_info *p)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(chips_init_xr); ++i)
		write_xr(chips_init_xr[i].addr, chips_init_xr[i].data);
	write_xr(0x81, 0x12);
	write_xr(0x82, 0x08);
	write_xr(0x20, 0x00);
	for (i = 0; i < ARRAY_SIZE(chips_init_sr); ++i)
		write_sr(chips_init_sr[i].addr, chips_init_sr[i].data);
	for (i = 0; i < ARRAY_SIZE(chips_init_gr); ++i)
		write_gr(chips_init_gr[i].addr, chips_init_gr[i].data);
	for (i = 0; i < ARRAY_SIZE(chips_init_ar); ++i)
		write_ar(chips_init_ar[i].addr, chips_init_ar[i].data);
	/* Enable video output in attribute index register */
	writeb(0x20, mmio_base + 0x780);
	for (i = 0; i < ARRAY_SIZE(chips_init_cr); ++i)
		write_cr(chips_init_cr[i].addr, chips_init_cr[i].data);
	for (i = 0; i < ARRAY_SIZE(chips_init_fr); ++i)
		write_fr(chips_init_fr[i].addr, chips_init_fr[i].data);
}