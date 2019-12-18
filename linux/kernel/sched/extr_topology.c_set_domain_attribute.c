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
struct sched_domain_attr {int relax_domain_level; } ;
struct sched_domain {int level; int flags; } ;

/* Variables and functions */
 int SD_BALANCE_NEWIDLE ; 
 int SD_BALANCE_WAKE ; 
 int default_relax_domain_level ; 

__attribute__((used)) static void set_domain_attribute(struct sched_domain *sd,
				 struct sched_domain_attr *attr)
{
	int request;

	if (!attr || attr->relax_domain_level < 0) {
		if (default_relax_domain_level < 0)
			return;
		else
			request = default_relax_domain_level;
	} else
		request = attr->relax_domain_level;
	if (request < sd->level) {
		/* Turn off idle balance on this domain: */
		sd->flags &= ~(SD_BALANCE_WAKE|SD_BALANCE_NEWIDLE);
	} else {
		/* Turn on idle balance on this domain: */
		sd->flags |= (SD_BALANCE_WAKE|SD_BALANCE_NEWIDLE);
	}
}