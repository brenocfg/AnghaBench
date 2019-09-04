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
typedef  scalar_t__ u8 ;
struct nphy_iq_comp {void* b1; void* a1; void* b0; void* a0; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 void* read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,void*) ; 

void
wlc_phy_rx_iq_coeffs_nphy(struct brcms_phy *pi, u8 write,
			  struct nphy_iq_comp *pcomp)
{
	if (write) {
		write_phy_reg(pi, 0x9a, pcomp->a0);
		write_phy_reg(pi, 0x9b, pcomp->b0);
		write_phy_reg(pi, 0x9c, pcomp->a1);
		write_phy_reg(pi, 0x9d, pcomp->b1);
	} else {
		pcomp->a0 = read_phy_reg(pi, 0x9a);
		pcomp->b0 = read_phy_reg(pi, 0x9b);
		pcomp->a1 = read_phy_reg(pi, 0x9c);
		pcomp->b1 = read_phy_reg(pi, 0x9d);
	}
}