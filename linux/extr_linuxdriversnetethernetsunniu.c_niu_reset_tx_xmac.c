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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTXMAC_SW_RST ; 
 int XTXMAC_SW_RST_REG_RS ; 
 int XTXMAC_SW_RST_SOFT_RST ; 
 int niu_set_and_wait_clear_mac (struct niu*,int /*<<< orphan*/ ,int,int,int,char*) ; 

__attribute__((used)) static int niu_reset_tx_xmac(struct niu *np)
{
	return niu_set_and_wait_clear_mac(np, XTXMAC_SW_RST,
					  (XTXMAC_SW_RST_REG_RS |
					   XTXMAC_SW_RST_SOFT_RST),
					  1000, 100, "XTXMAC_SW_RST");
}