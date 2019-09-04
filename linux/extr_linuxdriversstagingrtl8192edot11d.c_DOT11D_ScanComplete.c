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
struct rtllib_device {int dummy; } ;
struct rt_dot11d_info {int State; } ;

/* Variables and functions */
#define  DOT11D_STATE_DONE 130 
#define  DOT11D_STATE_LEARNED 129 
#define  DOT11D_STATE_NONE 128 
 int /*<<< orphan*/  Dot11d_Reset (struct rtllib_device*) ; 
 struct rt_dot11d_info* GET_DOT11D_INFO (struct rtllib_device*) ; 

void DOT11D_ScanComplete(struct rtllib_device *dev)
{
	struct rt_dot11d_info *pDot11dInfo = GET_DOT11D_INFO(dev);

	switch (pDot11dInfo->State) {
	case DOT11D_STATE_LEARNED:
		pDot11dInfo->State = DOT11D_STATE_DONE;
		break;
	case DOT11D_STATE_DONE:
		Dot11d_Reset(dev);
		break;
	case DOT11D_STATE_NONE:
		break;
	}
}