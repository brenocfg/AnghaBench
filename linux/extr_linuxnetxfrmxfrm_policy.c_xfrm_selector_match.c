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
struct xfrm_selector {int dummy; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int __xfrm4_selector_match (struct xfrm_selector const*,struct flowi const*) ; 
 int __xfrm6_selector_match (struct xfrm_selector const*,struct flowi const*) ; 

bool xfrm_selector_match(const struct xfrm_selector *sel, const struct flowi *fl,
			 unsigned short family)
{
	switch (family) {
	case AF_INET:
		return __xfrm4_selector_match(sel, fl);
	case AF_INET6:
		return __xfrm6_selector_match(sel, fl);
	}
	return false;
}