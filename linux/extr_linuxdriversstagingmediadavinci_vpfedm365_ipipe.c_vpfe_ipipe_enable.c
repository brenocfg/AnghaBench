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
struct vpfe_ipipeif_device {scalar_t__ input; } ;
struct vpfe_ipipe_device {scalar_t__ input; int /*<<< orphan*/  base_addr; } ;
struct vpfe_device {struct vpfe_ipipe_device vpfe_ipipe; struct vpfe_ipipeif_device vpfe_ipipeif; } ;

/* Variables and functions */
 scalar_t__ IPIPEIF_INPUT_MEMORY ; 
 scalar_t__ IPIPE_INPUT_NONE ; 
 int /*<<< orphan*/  IPIPE_SRC_EN ; 
 unsigned char regr_ip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw_ip (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void vpfe_ipipe_enable(struct vpfe_device *vpfe_dev, int en)
{
	struct vpfe_ipipeif_device *ipipeif = &vpfe_dev->vpfe_ipipeif;
	struct vpfe_ipipe_device *ipipe = &vpfe_dev->vpfe_ipipe;
	unsigned char val;

	if (ipipe->input == IPIPE_INPUT_NONE)
		return;

	/* ipipe is set to single shot */
	if (ipipeif->input == IPIPEIF_INPUT_MEMORY && en) {
		/* for single-shot mode, need to wait for h/w to
		 * reset many register bits
		 */
		do {
			val = regr_ip(vpfe_dev->vpfe_ipipe.base_addr,
				      IPIPE_SRC_EN);
		} while (val);
	}
	regw_ip(vpfe_dev->vpfe_ipipe.base_addr, en, IPIPE_SRC_EN);
}