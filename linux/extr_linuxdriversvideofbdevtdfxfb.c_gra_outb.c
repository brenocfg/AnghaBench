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
typedef  int /*<<< orphan*/  u32 ;
struct tdfx_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRA_D ; 
 int /*<<< orphan*/  GRA_I ; 
 int /*<<< orphan*/  vga_outb (struct tdfx_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void gra_outb(struct tdfx_par *par, u32 idx, u8 val)
{
	vga_outb(par, GRA_I, idx);
	wmb();
	vga_outb(par, GRA_D, val);
	wmb();
}