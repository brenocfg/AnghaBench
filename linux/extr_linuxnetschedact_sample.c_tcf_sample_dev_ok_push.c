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
struct net_device {int type; } ;

/* Variables and functions */
#define  ARPHRD_IPGRE 133 
#define  ARPHRD_NONE 132 
#define  ARPHRD_SIT 131 
#define  ARPHRD_TUNNEL 130 
#define  ARPHRD_TUNNEL6 129 
#define  ARPHRD_VOID 128 

__attribute__((used)) static bool tcf_sample_dev_ok_push(struct net_device *dev)
{
	switch (dev->type) {
	case ARPHRD_TUNNEL:
	case ARPHRD_TUNNEL6:
	case ARPHRD_SIT:
	case ARPHRD_IPGRE:
	case ARPHRD_VOID:
	case ARPHRD_NONE:
		return false;
	default:
		return true;
	}
}