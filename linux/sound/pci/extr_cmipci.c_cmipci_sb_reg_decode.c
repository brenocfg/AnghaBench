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
struct cmipci_sb_reg {unsigned long left_reg; unsigned long right_reg; unsigned long left_shift; unsigned long right_shift; unsigned long invert; unsigned long stereo; unsigned long mask; } ;

/* Variables and functions */

__attribute__((used)) static void cmipci_sb_reg_decode(struct cmipci_sb_reg *r, unsigned long val)
{
	r->left_reg = val & 0xff;
	r->right_reg = (val >> 8) & 0xff;
	r->left_shift = (val >> 16) & 0x07;
	r->right_shift = (val >> 19) & 0x07;
	r->invert = (val >> 22) & 1;
	r->stereo = (val >> 23) & 1;
	r->mask = (val >> 24) & 0xff;
}