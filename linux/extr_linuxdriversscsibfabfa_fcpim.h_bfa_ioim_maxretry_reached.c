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
typedef  scalar_t__ uint16_t ;
struct bfa_ioim_s {scalar_t__ iotag; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 scalar_t__ BFA_IOIM_RETRY_MAX ; 
 scalar_t__ BFA_IOIM_RETRY_TAG_OFFSET ; 
 int /*<<< orphan*/  BFA_TRUE ; 

__attribute__((used)) static inline bfa_boolean_t
bfa_ioim_maxretry_reached(struct bfa_ioim_s *ioim)
{
	uint16_t k = ioim->iotag >> BFA_IOIM_RETRY_TAG_OFFSET;
	if (k < BFA_IOIM_RETRY_MAX)
		return BFA_FALSE;
	return BFA_TRUE;
}