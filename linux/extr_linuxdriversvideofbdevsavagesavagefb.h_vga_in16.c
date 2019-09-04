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
typedef  int /*<<< orphan*/  u16 ;
struct savagefb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  savage_in16 (int,struct savagefb_par*) ; 

__attribute__((used)) static inline u16 vga_in16(int addr, struct savagefb_par *par)
{
	return savage_in16(0x8000 + addr, par);
}