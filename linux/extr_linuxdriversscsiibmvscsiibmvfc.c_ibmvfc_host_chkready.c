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

/* Variables and functions */
 int DID_NO_CONNECT ; 
 int DID_REQUEUE ; 
#define  IBMVFC_ACTIVE 134 
#define  IBMVFC_HALTED 133 
#define  IBMVFC_HOST_OFFLINE 132 
#define  IBMVFC_INITIALIZING 131 
#define  IBMVFC_LINK_DEAD 130 
#define  IBMVFC_LINK_DOWN 129 
#define  IBMVFC_NO_CRQ 128 

__attribute__((used)) static inline int ibmvfc_host_chkready(struct ibmvfc_host *vhost)
{
	int result = 0;

	switch (vhost->state) {
	case IBMVFC_LINK_DEAD:
	case IBMVFC_HOST_OFFLINE:
		result = DID_NO_CONNECT << 16;
		break;
	case IBMVFC_NO_CRQ:
	case IBMVFC_INITIALIZING:
	case IBMVFC_HALTED:
	case IBMVFC_LINK_DOWN:
		result = DID_REQUEUE << 16;
		break;
	case IBMVFC_ACTIVE:
		result = 0;
		break;
	}

	return result;
}