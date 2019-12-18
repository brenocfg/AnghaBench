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
struct xfrm_mode {int family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned int XFRM_MODE_MAX ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_mode* xfrm4_mode_map ; 
 struct xfrm_mode* xfrm6_mode_map ; 

__attribute__((used)) static const struct xfrm_mode *xfrm_get_mode(unsigned int encap, int family)
{
	const struct xfrm_mode *mode;

	if (unlikely(encap >= XFRM_MODE_MAX))
		return NULL;

	switch (family) {
	case AF_INET:
		mode = &xfrm4_mode_map[encap];
		if (mode->family == family)
			return mode;
		break;
	case AF_INET6:
		mode = &xfrm6_mode_map[encap];
		if (mode->family == family)
			return mode;
		break;
	default:
		break;
	}

	return NULL;
}