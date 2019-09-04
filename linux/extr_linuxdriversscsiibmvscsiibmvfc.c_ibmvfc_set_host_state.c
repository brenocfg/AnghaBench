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
struct ibmvfc_host {int state; } ;
typedef  enum ibmvfc_host_state { ____Placeholder_ibmvfc_host_state } ibmvfc_host_state ;

/* Variables and functions */
 int EINVAL ; 
#define  IBMVFC_HOST_OFFLINE 128 

__attribute__((used)) static int ibmvfc_set_host_state(struct ibmvfc_host *vhost,
				  enum ibmvfc_host_state state)
{
	int rc = 0;

	switch (vhost->state) {
	case IBMVFC_HOST_OFFLINE:
		rc = -EINVAL;
		break;
	default:
		vhost->state = state;
		break;
	}

	return rc;
}