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
struct pnp_dev {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ pnp_possible_config (struct pnp_dev*,int /*<<< orphan*/ ,int const,int) ; 

__attribute__((used)) static bool check_resources(struct pnp_dev *dev)
{
	static const resource_size_t base[] = {0x2f8, 0x3f8, 0x2e8, 0x3e8};
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(base); i++) {
		if (pnp_possible_config(dev, IORESOURCE_IO, base[i], 8))
			return true;
	}

	return false;
}