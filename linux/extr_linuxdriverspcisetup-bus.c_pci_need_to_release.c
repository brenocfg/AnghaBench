#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; TYPE_1__* parent; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 int IORESOURCE_PREFETCH ; 

__attribute__((used)) static bool pci_need_to_release(unsigned long mask, struct resource *res)
{
	if (res->flags & IORESOURCE_IO)
		return !!(mask & IORESOURCE_IO);

	/* check pref at first */
	if (res->flags & IORESOURCE_PREFETCH) {
		if (mask & IORESOURCE_PREFETCH)
			return true;
		/* count pref if its parent is non-pref */
		else if ((mask & IORESOURCE_MEM) &&
			 !(res->parent->flags & IORESOURCE_PREFETCH))
			return true;
		else
			return false;
	}

	if (res->flags & IORESOURCE_MEM)
		return !!(mask & IORESOURCE_MEM);

	return false;	/* should not get here */
}