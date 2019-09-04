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
struct fbtft_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	/* column address */
	write_reg(par, 0x2a, xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);

	/* Row address */
	write_reg(par, 0x2b, ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);

	/* memory write */
	write_reg(par, 0x2c);
}