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
typedef  int /*<<< orphan*/  u32 ;
struct fbtft_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_gamma(struct fbtft_par *par, u32 *curves)
{
	write_reg(par, 0xE0,
		  curves[0], curves[1], curves[2], curves[3],
		  curves[4], curves[5], curves[6], curves[7],
		  curves[8], curves[9], curves[10], curves[11],
		  curves[12], curves[13], curves[14], curves[15],
		  curves[16], curves[17], curves[18]);

	return 0;
}