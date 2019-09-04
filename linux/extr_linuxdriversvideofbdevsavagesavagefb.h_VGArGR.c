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
struct savagefb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,int /*<<< orphan*/ ,struct savagefb_par*) ; 

__attribute__((used)) static inline u8 VGArGR (u8 index, struct savagefb_par *par)
{
	vga_out8(0x3ce, index, par);
	return vga_in8(0x3cf, par);
}