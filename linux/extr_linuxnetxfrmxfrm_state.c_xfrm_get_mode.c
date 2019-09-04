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
struct xfrm_state_afinfo {int /*<<< orphan*/ * mode_map; } ;
struct xfrm_mode {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 struct xfrm_mode* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int XFRM_MODE_MAX ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,int,unsigned int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_state_afinfo* xfrm_state_get_afinfo (int) ; 

__attribute__((used)) static struct xfrm_mode *xfrm_get_mode(unsigned int encap, int family)
{
	struct xfrm_state_afinfo *afinfo;
	struct xfrm_mode *mode;
	int modload_attempted = 0;

	if (unlikely(encap >= XFRM_MODE_MAX))
		return NULL;

retry:
	afinfo = xfrm_state_get_afinfo(family);
	if (unlikely(afinfo == NULL))
		return NULL;

	mode = READ_ONCE(afinfo->mode_map[encap]);
	if (unlikely(mode && !try_module_get(mode->owner)))
		mode = NULL;

	rcu_read_unlock();
	if (!mode && !modload_attempted) {
		request_module("xfrm-mode-%d-%d", family, encap);
		modload_attempted = 1;
		goto retry;
	}

	return mode;
}