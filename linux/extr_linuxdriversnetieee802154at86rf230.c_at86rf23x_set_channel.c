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
struct at86rf230_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_CHANNEL ; 
 int at86rf230_write_subreg (struct at86rf230_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
at86rf23x_set_channel(struct at86rf230_local *lp, u8 page, u8 channel)
{
	return at86rf230_write_subreg(lp, SR_CHANNEL, channel);
}