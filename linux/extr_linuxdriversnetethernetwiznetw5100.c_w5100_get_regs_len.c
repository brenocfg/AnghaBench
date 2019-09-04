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
struct net_device {int dummy; } ;

/* Variables and functions */
 int W5100_COMMON_REGS_LEN ; 
 int W5100_S0_REGS_LEN ; 

__attribute__((used)) static int w5100_get_regs_len(struct net_device *ndev)
{
	return W5100_COMMON_REGS_LEN + W5100_S0_REGS_LEN;
}