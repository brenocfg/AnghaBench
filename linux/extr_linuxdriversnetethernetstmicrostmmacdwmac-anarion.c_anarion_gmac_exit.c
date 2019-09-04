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
struct platform_device {int dummy; } ;
struct anarion_gmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_RESET_CONTROL_REG ; 
 int /*<<< orphan*/  gmac_write_reg (struct anarion_gmac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void anarion_gmac_exit(struct platform_device *pdev, void *priv)
{
	struct anarion_gmac *gmac = priv;

	gmac_write_reg(gmac, GMAC_RESET_CONTROL_REG, 1);
}