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
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static int blank(struct fbtft_par *par, bool on)
{
	if (on)
		write_reg(par, 0xAE);
	else
		write_reg(par, 0xAF);
	return 0;
}