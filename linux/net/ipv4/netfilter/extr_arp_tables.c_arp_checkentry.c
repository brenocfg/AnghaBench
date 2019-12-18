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
struct arpt_arp {int flags; int invflags; } ;

/* Variables and functions */
 int ARPT_F_MASK ; 
 int ARPT_INV_MASK ; 

__attribute__((used)) static inline int arp_checkentry(const struct arpt_arp *arp)
{
	if (arp->flags & ~ARPT_F_MASK)
		return 0;
	if (arp->invflags & ~ARPT_INV_MASK)
		return 0;

	return 1;
}