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
struct rpi_power_domains {int /*<<< orphan*/  has_new_interface; struct rpi_power_domain* domains; } ;
struct rpi_power_domain {int domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpi_common_init_power_domain (struct rpi_power_domains*,int,char const*) ; 

__attribute__((used)) static void rpi_init_power_domain(struct rpi_power_domains *rpi_domains,
				  int xlate_index, const char *name)
{
	struct rpi_power_domain *dom = &rpi_domains->domains[xlate_index];

	if (!rpi_domains->has_new_interface)
		return;

	/* The DT binding index is the firmware's domain index minus one. */
	dom->domain = xlate_index + 1;

	rpi_common_init_power_domain(rpi_domains, xlate_index, name);
}