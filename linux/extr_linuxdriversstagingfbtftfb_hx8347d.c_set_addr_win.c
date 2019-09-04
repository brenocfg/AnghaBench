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
	write_reg(par, 0x02, (xs >> 8) & 0xFF);
	write_reg(par, 0x03, xs & 0xFF);
	write_reg(par, 0x04, (xe >> 8) & 0xFF);
	write_reg(par, 0x05, xe & 0xFF);
	write_reg(par, 0x06, (ys >> 8) & 0xFF);
	write_reg(par, 0x07, ys & 0xFF);
	write_reg(par, 0x08, (ye >> 8) & 0xFF);
	write_reg(par, 0x09, ye & 0xFF);
	write_reg(par, 0x22);
}